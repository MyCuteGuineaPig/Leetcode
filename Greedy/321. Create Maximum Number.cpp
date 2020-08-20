/*
321. Create Maximum Number


Given two arrays of length m and n with digits 0-9 representing two numbers. 
Create the maximum number of length k <= m + n from digits of the two. 
The relative order of the digits from the same array must be preserved. Return an array of the k digits.

Note: You should try to optimize your time and space complexity.

Example 1:

Input:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
Output:
[9, 8, 6, 5, 3]
Example 2:

Input:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
Output:
[6, 7, 6, 0, 4]
Example 3:

Input:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
Output:
[9, 8, 9]

*/

/*
试各种可能性，大的一个是answer
*/


class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int>a, b, ans, cand(k,0);
        /*
        所有可能性， i表示从nums1.中获取的个数，k - i表示从nums2中获取的个数，
        要保证从nums2中获取数 和 num1的获取的数有k个，

        但是当nums2.size() < k; 代表从nums2中最多获取nums2.size(), 至少有k-nums2.size()个需要从nums1中获取
        如果nums2.size() >=k, 就无所谓了，因为可以所有的都从nums2中拿
        max(k-(int)nums2.size(),0)

        */

        for(int i = max(k-(int)nums2.size(),0); i<=k && i<=nums1.size(); i++){
            maxArray(nums1, a, i);  maxArray(nums2, b, k-i);
            merge(a,b, cand);
            if(ans.empty() || isGreater(cand, 0,ans, 0)) ans = cand;
        }
        return ans;
    }
    
    void merge(vector<int>&a, vector<int>&b, vector<int>&cand){
        for(int i = 0, j = 0; i<a.size() || j<b.size(); ){
            if(isGreater(a, i, b, j)) cand[i+j] = a[i++];
            else  cand[i+j] = b[j++];
        }
    }
    
    /*
    isGreater 进来的 至少cand, ans有一个不是空,
    j == ans.size(), 表示j到头了，i没到头，表示i更大的，因为i, j前面一样，但i后面更大，
    比如a = [0,5],  b= [0],结果append顺序是a的0，a的5， b的0，如果先append b的0，结果就是 0, 0, 5,显然小了
    
    */
    bool isGreater(vector<int>&cand, int i,  vector<int>&ans, int j){
        while(i<cand.size() && j < ans.size() && cand[i] == ans[j]){
            i++; j++;
        }
        return j==ans.size() && i<cand.size() || (i<cand.size() && cand[i] > ans[j]);
    }
    
    /*
        nums.size() - i表示算上当前的，后面还有几个数可以操作，比如, 数有5个，当前index为2(第3个),后面还有第3个，第四个，第五个可以操作
        k - j表示如果删了当前j的，就是当j-1后，还有几个位置需要补上，
        比如k = 4 当前j=2，如果不删除2，后面还有j=3 需要补上 1 个数，如果删了j=2, 还需要 j = 2, j =3 补上，2个数 = 4-2
        需要补上的数必须小于等于可以操作的数

        但下面的j表示当前j的下一位，所以k-j 表示还需要多个数补上 - 1， 
        比如k = 4 j = 3,下一位需要填充的是 j =3, 上一位已经填充的是2，如果删了2，还需要填充2位
         4-3 + 1= 2. 所以是k - j < nums.size()-i 而不是 k - j <= nums.size()-i
    */

    void maxArray(vector<int>&nums, vector<int>& res, int k){
        res.resize(k,0);
        for(int i = 0, j = 0; i<nums.size(); i++){//j 控制res的
            while(j > 0 && j<=k && k - j < nums.size()-i && res[j-1] < nums[i]) j--;
            if(j<k) res[j++] = nums[i];
        }
    }
};

/*
上面的max Array也可以用stack来写
private int[] maxArray(int[] nums, int len) {
        Stack<Integer> stack = new Stack<Integer>();
        for (int i = 0; i < nums.length; i++) {
            while (stack.size() + nums.length - i > len && !stack.empty() && stack.peek() < nums[i]) {
                stack.pop();
            }
            if (stack.size() < len) {
                stack.push(nums[i]);
            }
        }
        int[] result = new int[len];
        for (int i = len - 1; i >= 0; i--) {
          result[i] = stack.pop(); 
        }
        return result;
    }
*/




/*
Solution 1中要尝试所有的解，
比如 [4, 9, 3, 2, 1, 8, 7, 6] 
当需要获取size 8的时候需要loop 一遍，当需要size = 7时候，还要loop一遍才能删除4
当size = 6的时候，还要loop 一遍，删除1， 当size = 5, 再删除1

我们可以发现，我们可以从上一次删除的位置开始继续删除，而不用重新loop，因为上一次删除是保证删除前面stack是descending 的
删除第一个, 4<9,删除
删除第二个,  9>3, skip, 3>2 skip, 2>1, skip, 发现1<8时候，删除1，
删除第三个,  2 < 8, 删除2，


*/
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result(k), tmp_result(k);
        vector<vector<int> > max_num1(k + 1), max_num2(k + 1);
        genDP(nums1, max_num1, k);  
        genDP(nums2, max_num2, k);
        for(int i = 0; i <= k; i++) {
            if(max_num1[i].size() + max_num2[k - i].size() < k)//从两个数从获取不够k个
                continue;
            merge(tmp_result, max_num1, max_num2, i, k);
            if(result.empty() || smaller(result, tmp_result))
                result = tmp_result;
        }
        return result;
    }
    
private:
    void genDP(vector<int>& nums, vector<vector<int> >& max_num, int k) {
        int i, start;
        for(start = 0; nums.size() > 0; start = (i == 0 ? 0 : i - 1)) {
            if(nums.size() <= k)
                max_num[nums.size()] = nums;
            for(i = start; i + 1 < nums.size() && nums[i] >= nums[i + 1]; i++);
            nums.erase(nums.begin() + i);
        }
    }
    
    void merge(vector<int>& tmp_result, vector<vector<int> >& max_num1, vector<vector<int> >& max_num2, int n, int k) {
        int i, j, ii, jj;
        for(i = j = 0; i < max_num1[n].size() && j < max_num2[k - n].size(); ) {
            //先跳过一样的, 比如对比a = [0, 5] 和 b = [0], 要先append a的0，然后a的5，再b的0， 否则会generate 0 0 5 < 0 5 0
            for(ii = i, jj = j; ii < max_num1[n].size() && jj < max_num2[k - n].size() && max_num1[n][ii] == max_num2[k - n][jj]; ii++, jj++);
            
            if(jj >= max_num2[k - n].size() || (ii < max_num1[n].size() && max_num1[n][ii] > max_num2[k - n][jj]))
                tmp_result[i + j] = max_num1[n][i++];
            else
                tmp_result[i + j] = max_num2[k - n][j++];
        }
        for( ; i < max_num1[n].size(); i++)
            tmp_result[i + j] = max_num1[n][i];
        for( ; j < max_num2[k - n].size(); j++)
            tmp_result[i + j] = max_num2[k - n][j];
    }
    
    bool smaller(vector<int>& result, vector<int>& tmp_result) {
        int i;
        for(i = 0; i < result.size() && result[i] == tmp_result[i]; i++);//只有等于的时候继续
        if(i < result.size() && result[i] < tmp_result[i])
            return true;
        return false;
    }
};


class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<int> best;
        for (int k1=max(k-n2, 0); k1<=min(k, n1); ++k1)
            best = max(best, maxNumber(maxNumber(nums1, k1),
                                    maxNumber(nums2, k-k1)));
        return best;
    }

    vector<int> maxNumber(vector<int> nums, int k) {
        int drop = nums.size() - k;
        vector<int> out;
        for (int num : nums) {
            while (drop && out.size() && out.back() < num) {
                out.pop_back();
                drop--;
            }
            out.push_back(num);
        }
        out.resize(k);
        return out;
    }

    vector<int> maxNumber(vector<int> nums1, vector<int> nums2) {
        vector<int> out;
        while (nums1.size() + nums2.size()) {
            vector<int>& now = nums1 > nums2 ? nums1 : nums2;
            out.push_back(now[0]);
            now.erase(now.begin());
        }
        return out;
    }

    /*
    第三个function 或者可以用
    vector<int> maxNumber(vector<int> nums1, vector<int> nums2) {
        vector<int> out;
        auto i1 = nums1.begin(), end1 = nums1.end();
        auto i2 = nums2.begin(), end2 = nums2.end();
        while (i1 != end1 || i2 != end2)
            out.push_back(lexicographical_compare(i1, end1, i2, end2) ? *i2++ : *i1++);
        return out;
    }
    
    */
};