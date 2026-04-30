/*
327. Count of Range Sum

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.




4. Why upper_bound - lower_bound works

We want:

count of values in [L, R]
Using prefix sums in BIT:

count(≤ R) - count(< L)
Which becomes:

getSum(R_index) - getSum(L_index)

That’s exactly:
upper_count - lower_count


*/

/*
// BIT 的 index 是从 1 开始的，因此我们需要统计的是
// prefix sums ∈ [sums[i] - upper, sums[i] - lower]

// 我们用 vec 做坐标压缩（0-based），所以：
int L = sums[i] - upper;
int R = sums[i] - lower;

// lower_bound(L):
// 返回的是 vec 中第一个 >= L 的位置（0-based）
// => 在 BIT 语义里(1 是起始index)，相当于 “第一个不小于 L 的前缀和位置”
// => 用于找到 < L 的分界点（左边界）
//不用Upper_bound, 因为从大于目标数 index-1, 得到的index的数可能是等于的
//但lower_bound 是从大于等于目标数 index-1, 得到的index的数一定是小于的

// upper_bound(R):
// 返回的是 vec 中第一个 > R 的位置（0-based）
// => 在 BIT 语义里(1 是起始index)，相当于 “最后一个 <= R 的位置 + 1”
// => 用于统计 ≤ R 的范围（右边界）


*/
class Solution {
public:
    void updateBIT(vector<long>&BIT, int i){
        while(i < BIT.size()) {
            BIT[i] += 1;
            i += i & -i;
        }
    }

    long BITsum(vector<long>&vec, int i) {
        long res = 0;
        while(i > 0) {
            res += vec[i];
            i -= (i & -i);
        }
        return res;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n  = nums.size();
        vector<long>sums(n+1);
        vector<long>sorted_sum(n+1);
        vector<long>BIT(n+2); // <--- this is important

        for(int i = 0; i < n; ++i) {
            sums[i+1] = sums[i]+ nums[i] ;
            sorted_sum[i+1] = sums[i]+ nums[i] ;
        }

        sort(sorted_sum.begin(), sorted_sum.end());
        
        int res = 0;
        for(int i = 0; i<=n; ++i) {
            int lower_count = BITsum(BIT, lower_bound(sorted_sum.begin(), sorted_sum.end(), sums[i] - upper) - sorted_sum.begin());
            int upper_count = BITsum(BIT, upper_bound(sorted_sum.begin(), sorted_sum.end(), sums[i] - lower) - sorted_sum.begin());
            //因为BIT Tree index start 为1， 需要找的是[sums[i]-upper, sums[i]-lower]
            //upper_bound(sums[i]-lower) => 以0为index, 第一个大于sums[i]-lower的数 (如果以1为index，需要减1, 最后一个在sums[i]-lower范围内的数)
            //lower_bound(sums[i]-upper) 也是以0为index, 第一个 （如果以1为index，需要减1,  第一个不在sums[i]-lower范围内的数）

            res += upper_count - lower_count;
            updateBIT(BIT, 1+lower_bound(sorted_sum.begin(), sorted_sum.end(), sums[i]) - sorted_sum.begin());
            //+1 因为BIT index 起始值是1 
            //update BIT 是把当前的sums[i] 插入到BIT中，
            //后续的sums[j] (j>i) 就可以通过getSum来统计有多少个sums[j] 满足 sums[j] - sums[i] ∈ [lower, upper]
           
            //or  update(BIT, upper_bound(vec.begin(), vec.end(), sums[i]) - vec.begin());
        }
        return res;
    }
};




/*
Merge Sort的解:
 原始的sum[i] 代表前i个在num中数的和
 每次mergesort 返回的left,right 已经是sort好的sum，且left中的sum 一定是在right任何sum原有数左面的sum,
  比如left =[0,3], right = [5,6], [3,4] 分别是前4和前3的sum, 【5，6】一定是前5以后（包括前五）的sum
  比如【5，6】代表前7和前5个sum 这样子5-0 = 5 代表从5位到第6位的sum，6-3 = 3代表第4位的sum

然后因为left，right是sort的，所以找low,high index, count = high-low,
low 是第一个sum difference满足sum[r]-sum[l]>=lower的index, high是第一个不满足sum[r]-sum[l]<=upper的index

*/
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int size = nums.size();
        vector<long>sums(size+1,0);//需要用long，否则会overflow
        for(int i = 0; i<size;i++)
            sums[i+1] = sums[i]+nums[i];
        return mergeSortCount(sums,lower,upper,0,size+1);
    }
    
    int mergeSortCount(vector<long>&sums, const int & lower, const int & upper, int start, int end){
        if(end-start<=1) return 0;
        int mid = (start+end)>>1;
        int count = mergeSortCount(sums,lower, upper, start, mid) + mergeSortCount(sums,lower, upper, mid, end);
        int low = mid, high = mid, t = mid;
        vector<int>tempSum;
        for(int i = start; i<mid; i++){
            while(low < end && sums[low]-sums[i]<lower)low++;
            while(high < end && sums[high]-sums[i]<=upper)high++;
            while(t<end && sums[t]<sums[i]) tempSum.push_back(sums[t++]);
            tempSum.push_back(sums[i]);
            count += high - low;
        }
        
        move(tempSum.begin(),tempSum.end(),sums.begin()+start);
        
        return count;
    }
};


 class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int size=nums.size();
        if(size==0)  return 0;
        vector<long> sums(size+1, 0);
        for(int i=0; i<size; i++)  sums[i+1]=sums[i]+nums[i];
        cout<<" sum ";
        for(auto i: sums)
            cout<<i<<" ";
        cout<<endl;
        return help(sums, 0, size+1, lower, upper);
    }
    
    /*** [start, end)  ***/
    int help(vector<long>& sums, int start, int end, int lower, int upper){
        cout<<" in "<<start<<" end "<<end<<endl;
        /*** only-one-element, so the count-pair=0 ***/
        if(end-start<=1)  return 0;
        int mid=(start+end)/2;
        int count=help(sums, start, mid, lower, upper)
                + help(sums, mid, end, lower, upper);
        cout<<" after "<<start<<" end "<<end<<" mid "<<mid<<" count "<<count<<endl;
        int low=mid, high=mid, t=mid, len=0;
        /*** cache stores the sorted-merged-2-list ***/
        /*** so we use the "len" to record the merged length ***/
        vector<long> cache(end-start, 0);
        for(int i=start, s=0; i<mid; i++, s++){
            /*** wrong code: while(m<end && sums[m++]-sums[i]<lower);  ***/
            while(low<end && sums[low]-sums[i]<lower) low++;
            while(high<end && sums[high]-sums[i]<=upper) high++;
            cout<<" loop i "<<i<<"  s "<<s<<" low "<<low<<" high "<<high<<endl;
            count+=high-low;
            cout<<" count = "<<count<<endl;
            /*** cache will merge-in-the-smaller-part-of-list2 ***/
            while(t<end && sums[t]<sums[i]) {
                cout<<" in while "<<i<<" t "<<t<<" end "<<end<<endl;
                cache[s++]=sums[t++];
            }
            cache[s]=sums[i];
            len=s;
        }
        cout<<" cache start "<<start<<" end "<<end<<" : ";
        for(auto i: cache)
            cout<<i<<" ";
        cout<<" len "<<len<<endl;
        for(int i=0; i<=len; i++)  sums[start+i]=cache[i];
        cout<<" sums start "<<start<<" end "<<end<<" : ";
        for(auto i: sums)
            cout<<i<<" ";
        cout<<endl;
        return count;
    }
};