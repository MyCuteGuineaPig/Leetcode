//top-down
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];
        vector<int>dp(nums.size(),0); //max number amount at stage i 
        dp[0] = nums[0];
        dp[1] = max(nums[1],nums[0]);

        for(int i = 2; i<nums.size();i++){
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        return dp[nums.size()-1];
    }
};



class Solution {
public:
    int rob(vector<int>& nums) {
            int a = 0;
    int b = 0;
    
    for (int i=0; i<nums.size(); i++)
    {
        if (i%2==0)
        {
            a = max(a+nums[i], b);
        }
        else
        {
            b = max(a, b+nums[i]);
        }
    }
    
    return max(a, b);
    }
};



class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return max(nums[0],nums[1]);
        int p2 = nums[0], p1 = max(nums[1],nums[0]), tot = 0;
        for(int i = 2; i<nums.size(); i++){
            tot = max(nums[i]+p2, p1);
            p2 = p1;
            p1 = tot; 
        }
        return tot;
    }
};


//top-down
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty())
            return 0;
        vector<int>dp(nums.size(),-1); //避免[0,0,0,0,0]
        return helper(nums, dp, nums.size()-1);
    }
    
    int helper(vector<int>&nums, vector<int>&dp, int i){
        if(i == 0){
            return dp[i] = nums[i];
        }else if(i == 1){
            return dp[i] = max(nums[0], nums[1]);
        }
        if(dp[i] >= 0)
            return dp[i];
        return dp[i] =  max(helper(nums, dp, i-1), helper(nums, dp, i-2)+nums[i]);
    }
};