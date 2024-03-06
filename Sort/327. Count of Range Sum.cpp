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




*/

class Solution {
public:
    void update(vector<long>& nums, int i){
        while(i < nums.size()){
            nums[i] += 1;
            i += i & -i;
        }
    }
    int getSum(vector<long>& nums,int i){
        int tot = 0;
        while(i){
            tot += nums[i];
            i -= i & -i;
        }
        return tot;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long>vec(n+1); 
        vector<long>sums(n+1);
        vector<long>BIT(n+2);
        long cur = 0;
        for(int i = 0; i < n; ++i){
            cur += nums[i];
            vec[i+1] = cur;
            sums[i+1] = cur;
        }
        sort(vec.begin(), vec.end());
        int res = 0;
        for(int i = 0; i <= n; ++i){
            int lower_count = getSum(BIT, lower_bound(vec.begin(), vec.end(), sums[i]-upper) - vec.begin());
            int upper_count = getSum(BIT, upper_bound(vec.begin(), vec.end(), sums[i]-lower) - vec.begin());
            res += (upper_count - lower_count);
            update(BIT, 1+lower_bound(vec.begin(), vec.end(), sums[i]) - vec.begin());
            //如果不加1,  lower_bound(vec.begin(), vec.end(), sums[i])  = 0 时候就有问题了
            //更新大于sum[i] index 的第一个点, upper_count 的时候就会算进去，因为比如upper_bound
            //lower_count 算不算无所谓，因为 如果lower_count 算, upper_count 也算进去了
           
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