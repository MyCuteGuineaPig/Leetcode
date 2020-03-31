/*
198. House Robber
https://leetcode.com/problems/house-robber/description/


You are a professional robber planning to rob houses along a street.
 Each house has a certain amount of money stashed, 
 the only constraint stopping you from robbing each of them is that 
 adjacent houses have security system connected and it will automatically 
 contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, 
determine the maximum amount of money you can rob tonight without alerting the police.

*/

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