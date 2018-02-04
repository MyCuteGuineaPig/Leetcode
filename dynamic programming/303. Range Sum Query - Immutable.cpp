/*

303. Range Sum Query - Immutable
https://leetcode.com/problems/range-sum-query-immutable/description/

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.


*/

class NumArray {
public:
    vector<int>dp;
    
    NumArray(vector<int> nums) {
        dp.resize(nums.size(),0);
        if(nums.size()>0){
            dp[0] = nums[0];
            for(int i = 1; i<nums.size();i++){
                dp[i] = dp[i-1] + nums[i];
            }
        }
    }
    
    int sumRange(int i, int j) {
        return i==0? dp[j] : dp[j] - dp[i-1];
    }
};