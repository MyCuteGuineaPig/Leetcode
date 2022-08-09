class Solution {
public:
    bool validPartition(vector<int>& nums) {
        if (nums.size() < 2) 
            return false;
        vector<int>dp(nums.size()+1,0);
        dp[0] = 1;
        for(int i = 1; i<nums.size(); ++i){
            if(nums[i-1] == nums[i])
                dp[i+1] |= dp[i-1];
            if(i> 1 && nums[i] == nums[i-1] && nums[i] == nums[i-2])
                dp[i+1] |= dp[i-2];
            if(i>1 && nums[i] == nums[i-1] + 1 && nums[i] == nums[i-2]+2)
                dp[i+1] |= dp[i-2];
        }
        return dp.back();
    }
};

class Solution {
public:
    bool validPartition(vector<int>& nums) {
        bool dp[4] = {true, false, nums[0] == nums[1], false};
        for (int i = 2; i < nums.size(); ++i) {
            bool two = nums[i] == nums[i - 1];
            bool three = (two && nums[i] == nums[i - 2]) || (nums[i] - 1 == nums[i - 1] && nums[i] - 2 == nums[i - 2]);
            dp[(i + 1) % 4] = (dp[(i - 1) % 4] && two) || (dp[(i - 2) % 4] && three);
        }
        return dp[nums.size() % 4];
    }
};


class Solution {
public:
    bool topDown(vector<int>& nums, int index, vector<int>&dp){
        if(index == -1) return 1;
        if (dp[index+1])
            return dp[index + 1];
        return dp[index+1] = (index >= 1 && nums[index] == nums[index-1] && topDown(nums,index-2, dp)) ||
             (index >= 2 && nums[index] == nums[index-1] && nums[index] == nums[index-2] && topDown(nums,index-3, dp)) ||
            (index >= 2 && nums[index] == nums[index-1] + 1 && nums[index] == nums[index-2] + 2 && topDown(nums,index-3, dp));
                        
    }
    
    bool validPartition(vector<int>& nums) {
        if (nums.size() <= 1) return false;
        vector<int>dp(nums.size()+1, 0);
        
        return topDown(nums, nums.size()-1, dp);
    }
};