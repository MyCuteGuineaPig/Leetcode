/*
164. Maximum Gap

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

Example 1:

Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
Note:

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
Try to solve it in linear time/space.

*/

/*
Bucket Sort

min + (n - 1)minStep = max

(n - 1)minStep = max - min

minStep = ceil((max - min) / (n - 1)) 
(max gap的最小的值为minStep, minstep是每个区间的平均值, 要是有gap小于minstep,肯定有值大于minstep,因为n-1个数加起来的和等于max-min)


If we set the bucket size clever(relatively small), 
we can ensure that the max gap cannot be in same bucket. 
In worst case each successive numbers have same gap. For example, we have 1, 3, 5 the gap and max gap is (5 - 1) / 2. 
Largest - Smallest, two gaps.

Based on this, we only need to compare max number in this bucket and min number in next bucket to get the relatively large gap 
and find out which two bucket have the largest gap.

Suppose there are N elements in the array, the min value is min and the max value is max. 
Then the maximum gap will be no smaller than ceiling[(max - min ) / (N - 1)]. (因为min, max之间有n-1区间的 i+1 减去i)

Let gap = ceiling[(max - min ) / (N - 1)]. We divide all numbers in the array into n-1 buckets, 
where k-th bucket contains all numbers in [min + (k-1)gap, min + k*gap). 
Since there are n-2 numbers that are not equal min or max and there are n-1 buckets, 
at least one of the buckets are empty. We only need to store the largest number and the smallest number in each bucket.

After we put all the numbers into the buckets. We can scan the buckets sequentially and get the max gap.


最大gap 在bucket 之间 不在bucket内的原因是：
假如我们有N个数，average gap 是 x, 

For example [1,2,4,5] we have gap array [1,2,1], the average gap x = (1+2+1)/3.

平均gap = (max-min)/(N-1), 平均gap表示有个gap 比它大，有的gap 比他小，因为我们要找最大gap，所以找bucket之间的，

如果刚好gap 都一样，比如[1,4,7,10], average gap = 3,  正好分成了4个bucket, 每一个数在一个bucket 

*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int n = nums.size();
        if(n<=1) return 0;
        int maxn = *max_element(nums.begin(),nums.end());
        int minn = *min_element(nums.begin(),nums.end());
        double gap = (double)(maxn-minn)/(double)(n-1);
        if(gap == 0) return 0;  //防止接下来的division by zero,比如[1,1,1,1] gap = 0
        vector<int>maxv(n,numeric_limits<int>::min());
        vector<int>minv(n,numeric_limits<int>::max());      
        for(auto i: nums)
        {
            int ind = (i-minn)/gap;
            maxv[ind] = max(maxv[ind], i); 
            minv[ind] = min(minv[ind],i);
        }

        
        int res = 0, prev = maxv[0];
        for(int i = 1; i<n; i++){
            if(minv[i]== numeric_limits<int>::max()) continue;
            res = max(res, minv[i]-prev);
            prev = maxv[i];
        }
        return res;
    }
};


//2020
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if(nums.size() <= 1) return 0;
        int maxn = *max_element(nums.begin(), nums.end());
        int minn = *min_element(nums.begin(), nums.end());
        if( maxn == minn) 
            return 0;
        double gap = (double)(maxn - minn)/(double)nums.size();
        vector<vector<int>> p((maxn - minn)/gap+1);
        for(auto i: nums){
            int bucket = (i -minn) / gap;
            if (p[bucket].empty()){
                p[bucket] = vector<int>(2,0);
                p[bucket][0] = i;
                p[bucket][1] = i;
            }
            else{
                p[bucket][0] = min(p[bucket][0], i);
                p[bucket][1] = max(p[bucket][1], i);
            }
        }
        int res = 0, prev = maxn + 1;
        for(int i = 0; i<p.size(); ++i){
            if(!p[i].empty()){
                if (prev != maxn+1) 
                    res = max(res, p[i][0] - prev);
                prev = p[i][1];
            }
        }
        return res;
    }
};


class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int n = nums.size();
        if(n<=1) return 0;
        int maxn = *max_element(nums.begin(),nums.end());
        long exp = 1, base = 16;
        vector<int> aux(nums.size());
        while(maxn/exp>0){
            vector<int>count(base,0);
            for(auto i: nums)
                count[(i/exp)%base]++;

            for(int i = 1; i<base; i++)
                count[i] += count[i-1];

            for(int i = n-1; i>=0; i--) //必须从后往前，因为之前的digit的是sort，大的digit在最后面，count是从这个位数的最后一个位置开始往前
                aux[--count[(nums[i]/exp)%base]] = nums[i];
          
          /*
          比如第一次sort完是  20, 10, 21, 11
          第二次, sort 顺序是 10, 11, 20, 21  :  20 排21 前面, 因为根据上一位sort 结果, 1 > 0
          */
          
            exp *= base;
            nums = aux;
        }
        int res = 0;
        for(int i = 1; i<n; i++)
            res = max(res, nums[i]-nums[i-1]);
        return res;
    }
};
