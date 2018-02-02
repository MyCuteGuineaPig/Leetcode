/*

53. Maximum Subarray

https://leetcode.com/problems/maximum-subarray/description/

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

*/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size(),0);
		dp[0] = nums[0];
		int maxsum = nums[0];
		for(int i = 1; i<nums.size();i++){
			dp[i] = dp[i-1] + nums[i] > nums[i] ? dp[i-1] + nums[i]: nums[i]; 
			// dp 中存入到i为止（包括i）最大的sum， 如果dp【i]+nums[i] 小于nums[i] 
			// 代表现在只包括nums[i] 是最大sum
			maxsum = maxsum > dp[i] ? maxsum : dp[i]; // 到i为止最大的sum 和 maxsum 对比
		}
		return maxsum;
    }
};