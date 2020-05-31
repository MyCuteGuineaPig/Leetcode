/*
backtracking 会time out
*/

/*
DP
*/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int>dp(target+1,0);
        dp[0] = 1;
        sort(nums.begin(),nums.end());
        for(int i = 1; i<=target;i++){
            for(int j = 0; j<nums.size() && nums[j]<=i; j++)
                dp[i] += dp[i-nums[j]];
        }
        return dp[target];
    }
};



//2020 Top-Down
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<long long>dp(target+1,-1);
        dp[0] = 1;
        return topDown(nums, dp, target);
    }
    
    int topDown(vector<int>&nums, vector<long long>&dp, int target){
        if(dp[target] != -1)
            return dp[target];
        int cur = 0;
        for(auto j: nums)
            if(j<=target)
                cur += topDown(nums,dp, target-j);
        return dp[target] = cur;
    }
};

//2020 Bottom-Up
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<long long>dp(target+1,0);
        dp[0] = 1;
        for(int i = 1; i<=target; ++i){
            int cur = 0;
            for(auto j: nums){
                if(j <= i && cur + dp[i-j]<numeric_limits<int>::max())//个别数很大，阻止overflow
                    cur += dp[i-j];
            }
            dp[i] = cur;
        }
        return dp.back();
    }
};
