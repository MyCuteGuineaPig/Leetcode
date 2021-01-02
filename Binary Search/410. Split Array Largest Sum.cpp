/*
410. Split Array Largest Sum

Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. 
Write an algorithm to minimize the largest sum among these m subarrays.

Note:

/*
The answer is between maximum value of input array numbers and sum of those numbers.
Use binary search to approach the correct answer. We have l = max number of array; r = sum of all numbers in the array;Every time we do mid = (l + r) / 2;
Use greedy to narrow down left and right boundaries in binary search.
3.1 Cut the array from left.
3.2 Try our best to make sure that the sum of numbers between each two cuts (inclusive) is large enough but still less than mid.
3.3 We'll end up with two results: either we can divide the array into more than m subarrays or we cannot.
*/
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        long l = *max_element(nums.begin(),nums.end());
        long r = accumulate(nums.begin(),nums.end(),0);
        if(m==1) return r;
        if(m==nums.size()) return l;
        while(l<r){
            long mid = l + (r-l)/2;
            if(isValid(nums,m,mid)) r = mid;
            else l = mid+1;
        }
        return l;
    }

    bool isValid(vector<int>& nums, int cut, long target){
        long cursum = 0;
        for(long n: nums){
            cursum += n;
            if(cursum<=target) continue;
            cursum = n;
            if(--cut==0) return false;
        }
        return true;
    }
};



//2020
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int tot = 0;
        for(auto i : nums) tot += i;
        int i = 0, j = tot;
        while(i < j){
            int mid = i + (j-i)/2;
            if(cut(nums, m, mid)) j = mid;
            else i = mid + 1;
        }
        return i;
    }
    
    bool cut(vector<int>& nums, int m, int sum){
        int cursum = 0;
        for(auto i: nums){
            if(i > sum || cursum + i > sum && m == 1) return false;
            cursum += i;
            if(cursum > sum){
                cursum = i;
                --m;
            }
        }
        return true;
    }
};




//2020 DP
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<int>dp(n+1);
        for(int i = 0, cur = 0; i<nums.size(); ++i){
            cur += nums[i];
            dp[i+1] = cur;
        }
        
        for(int i = 1; i<m; ++i){
            for(int j = nums.size()-1; j>=0; --j){
                for(int k = j, cur = 0; k>=0; --k){
                    cur += nums[k];
                    dp[j+1] = min(dp[j+1], max(cur, dp[k]));
                    
                }
            }
        }
        return dp.back();
    }
};



class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<int>>dp(n+1, vector<int>(m,-1));
        for(int i = 0, cur = 0; i<nums.size(); ++i){
            cur += nums[i];
            dp[i+1][0] = cur;
        }
        return topDown(nums, dp, m-1,n-1);
    }
    
    int topDown(vector<int>& nums, vector<vector<int>>&dp, int m, int i){
        if(m == 0)
            return dp[i+1][m];
        if(dp[i+1][m] >= 0)
            return dp[i+1][m];
        dp[i+1][m] = numeric_limits<int>::max();
        for(int j = i, cur = 0; j>=0; --j){
            cur += nums[j];
            dp[i+1][m] = min(dp[i+1][m], max(topDown(nums, dp, m-1, j-1), cur));
        }
        return dp[i+1][m];
    }
};