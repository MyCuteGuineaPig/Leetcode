/*
45. Jump Game II
https://leetcode.com/problems/jump-game-ii/description/

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)


*/
class Solution {
public:
    int jump(vector<int>& nums) {
        int jump = 0, curfarthest = 0, curend = 0;
        for(int i = 0; i<nums.size() && curend<nums.size()-1;i++){
            curfarthest = max(curfarthest,i+nums[i]);
            if(curend == i){
                jump++;
                curend = curfarthest;
            }
        }
        return jump;
    }
};
/*
               2      3     1     1  4
    farthest  2       4     4     
    curend    0->2    2   2->4


*/
