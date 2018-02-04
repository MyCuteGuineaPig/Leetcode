/*
213. House Robber II

Note: This is an extension of House Robber.

After robbing those houses on that street, 
the thief has found himself a new place for his thievery 
so that he will not get too much attention. 
This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. 
Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house,
 determine the maximum amount of money you can rob tonight without alerting the police.


*/

/*

This problem is a little tricky at first glance. However, if you have finished the House Robber problem, this problem can simply be decomposed into two House Robber problems.
Suppose there are n houses, since house 0 and n - 1 are now neighbors, we cannot rob them together and thus the solution is now the maximum of

Rob houses 0 to n - 2;
Rob houses 1 to n - 1.
The code is as follows. Some edge cases (n < 2) are handled explicitly.

*/

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return max(nums[0], nums[1]);
        return max(singlehouseRobber(nums, 0, nums.size()-2),singlehouseRobber(nums, 1, nums.size()-1));
    }
    
    int singlehouseRobber(vector<int>& nums,int start, int end){
        vector<int>dp(nums.size(),0);
        dp[start] = nums[start];
        dp[start+1] = max(nums[start+1],nums[start]);
        for(int i = start+2; i<=end; i++){
            dp[i] = max(nums[i]+dp[i-2], dp[i-1]);
        }
        return dp[end];
    }
};


class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size(); 
        if (n < 2) return n ? nums[0] : 0;
        return max(robber(nums, 0, n - 2), robber(nums, 1, n - 1));
    }
private:
    int robber(vector<int>& nums, int l, int r) {
        int pre = 0, cur = 0;
        for (int i = l; i <= r; i++) {
            int temp = max(pre + nums[i], cur);
            pre = cur;
            cur = temp;
        }
        return cur;
    }
};