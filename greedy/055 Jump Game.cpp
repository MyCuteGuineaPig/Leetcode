/*
55 Jump Game
https://leetcode.com/problems/jump-game/description/
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.


*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int i = 0,reach = 0;
        for(;i<nums.size()&&i<=reach; i++)
            reach = max(reach, i+nums[i]);
        return reach >= nums.size()-1;
    }
};

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int goal=n-1, i;
        for (i=n; i--;){
          if (i+nums[i] >= goal){//goal is current max reach index from end to begin
              goal=i;
          }
        }
        return !goal;
    }
};


