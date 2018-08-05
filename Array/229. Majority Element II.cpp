/*
229. Majority Element II

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Note: The algorithm should run in linear time and in O(1) space.

Example 1:

Input: [3,2,3]
Output: [3]
Example 2:

Input: [1,1,1,3,3,2,2,2]
Output: [1,2]
*/

//Boyer-Moore Majority Vote algorithm
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if(nums.empty()) return {};
        int count[2] = {0};
        int ans[2] = {0};
        for(auto n: nums){
            if (n == ans[0]) count[0]++;
            else if(n == ans[1]) count[1]++;
            else if(count[0] == 0) count[0] = 1, ans[0] = n;
            else if(count[1] == 0) count[1] = 1, ans[1] = n;
            else count[0]--, count[1]--;
        }
        //cannot guanratee first pass potential answer count is bigger than 1/3
        count[0] = 0; count[1] = 0; 
        for(auto n: nums)
            if(n == ans[0]) count[0]++;
            else if(n == ans[1]) count[1]++;
        
        if(count[0] >nums.size()/3 && count[1]>nums.size()/3) return {ans[0], ans[1]};
        else if(count[0]>nums.size()/3) return {ans[0]};
        else if(count[1]>nums.size()/3) return {ans[1]};
        else return {};
    }
};