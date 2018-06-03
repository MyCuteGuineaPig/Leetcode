/*
283. Move Zeroes

Given an array nums, write a function to move all 0's to the end of it 
while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.


*/



class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for(int i = 0; i<nums.size();i++){
            if(nums[i]!=0)
                swap(nums[i],nums[j++]);
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int pos = 0;
        for (const auto& num : nums) {
            if (num) {
                nums[pos++] = num;
            }
        }
        fill(next(nums.begin(), pos), nums.end(), 0);
    }
};