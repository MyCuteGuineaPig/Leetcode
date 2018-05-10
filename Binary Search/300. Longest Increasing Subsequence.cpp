/*
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?


*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int>dp(nums.size(),1);
        for(int i = 0; i<nums.size();i++)
            for(int j = 0; j<i;j++)
                if(nums[i]>nums[j])
                    dp[i] = max(dp[i],dp[j]+1);
        return *max_element(dp.begin(),dp.end());
    }
};



/*
dp with memoization 
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int>dp(nums.size(),-1);
        for(int i = 0; i<nums.size();i++)
            helper(nums,dp,i);
        return *max_element(dp.begin(),dp.end());
    }

    int helper(vector<int>& nums, vector<int> &dp, int i){
        if(dp[i]!=-1)
            return dp[i];
        dp[i] = 1;
        for(int j = i-1; j>=0; j--){
            if(nums[i]>nums[j])
                dp[i] = max(dp[i], helper(nums,dp,j)+1);
        }
         return dp[i];
    }

};


/*
tails is an array storing the smallest tail of all increasing subsequences with length i+1 in tails[i].
For example, say we have nums = [4,5,6,3], then all the available increasing subsequences are:

len = 1   :      [4], [5], [6], [3]   => tails[0] = 3
len = 2   :      [4, 5], [5, 6]       => tails[1] = 5
len = 3   :      [4, 5, 6]            => tails[2] = 6
We can easily prove that tails is a increasing array. Therefore it is possible to do a binary search 
in tails array to find the one needs update.

Each time we only do one of the two:

(1) if x is larger than all tails, append it, increase the size by 1
(2) if tails[i-1] < x <= tails[i], update tails[i]
Doing so will maintain the tails invariant. The the final answer is just the size.
*/

/*
dp[i] 存的是 longest increasing array 长度为len = i+1，最小的tail数字
比如dp[2,5] 代表当长度为1时，长度为1是[2], 当increasing subarray长度为2是，组成subarray 末尾最后一位数最小是5 
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>tail;
        for(int n : nums){
            int i = 0, j = tail.size();
            while(i<j){
                int mid = i + (j-i)/2;
                if(tail[mid]<n)
                    i = mid +1;
                else 
                    j = mid;
            }
            if(i>=tail.size())
                tail.push_back(n);
            else 
                tail[i] = n;
        }
        return tail.size();
    }
};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>tail;
        for(int n : nums){
            int i = 0, j = tail.size();
            if(tail.empty() || tail.back()<n)
                tail.push_back(n);
            else {
                auto it = lower_bound(tail.begin(),tail.end(), n);
                tail[it-tail.begin()] = n;
            }
        }
        return tail.size();
    }
};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> r;
        
        for(auto v : nums) {
            auto p = std::lower_bound(r.begin(), r.end(), v);
            if (r.end() == p)
                r.push_back(v);
            else
                *p = v;
        }
        return r.size();
    }
};