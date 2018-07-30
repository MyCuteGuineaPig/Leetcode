/*
16. 3Sum Closest

Given an array nums of n integers and an integer target, 
find three integers in nums such that the sum is closest to target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


*/


/*
通过sort 控制两个pointer的位置

目标是让temp sum 离target 越来越近
如果temp sum 小于target, j++, 把temp sum 变大

如果temp sum 大于target, k--, 把temp sum 变小


*/


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for(int i = 0; i<nums.size()-2; i++){
            for(int j = i+1, k = nums.size()-1; j<k;){
                int temp = nums[i] + nums[j] + nums[k];
                if(abs(temp - target) < abs(res-target))
                    res =  nums[i] + nums[j] + nums[k];
                if( temp< target){
                    j++;
                }else if(temp == target)
                    return target;
                else k--;
            }
        }
        return res;
    }
};



//skipping duplicate
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for(int i = 0; i<nums.size()-2; i++){
            for(int j = i+1, k = nums.size()-1; j<k;){
                int temp = nums[i] + nums[j] + nums[k];
                if(abs(temp - target) < abs(res-target))
                    res =  nums[i] + nums[j] + nums[k];
                if( temp< target){
                    j++;
                    while (j< k && nums[j] == nums[j-1]) j++;
                }else if(temp == target)
                    return target;
                else {
                    k--;
                    while (j< k && nums[k] == nums[k+1])  k--;
                }
            }
            while(i+1 < nums.size() && nums[i] == nums[i+1]) i++;
        }
        return res;
    }
};