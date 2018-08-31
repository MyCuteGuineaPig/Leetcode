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

/*
跟045	Jump Game II 相像，找目前可以跳的范围内(这一跳加上下一跳)最远的点,curfastest, 
当到之前设定的点currend时，更新最远点为 curend 为curfast

如果最远的点 == i, 就是不能更前进的时候，return false
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int curfast = 0, curend = 0;
        for(int i = 0; i<nums.size()-1; i++){
            curfast = max(i+nums[i], curfast);
            if(curfast == i) return false;
            if(curend == i) curend = curfast;
        }
        return true;
    }
};


class Solution {
public:
    bool canJump(vector<int>& nums) {
        int i = 0,reach = 0;
        for(;i<nums.size()&&i<=reach; i++)
            reach = max(reach, i+nums[i]);
        return reach >= nums.size()-1;
    }
};

//看是0点的，只要是大于0点都没有威胁，只有有0的点可以return true
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()<2) return true;
        int zero = 0, n = nums.size();
        bool res = true;
        for(; zero<n-1; zero++){
            if(nums[zero]==0){
                bool temp = false;
                for(int i=0; i<zero; i++){
                    if(nums[i]>zero-i) temp = true;
                }
                res = res && temp;
            }
        }
        return res;
    }
};


// 看前进的step
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size=nums.size();
        int step=nums[0];
        for(int i=1;i<size;++i){
            step--;
            if(step<0)
            return false;
            if(nums[i]>step)
            step=nums[i];
        }
        return true;
    }
};
/*
Solution 2: 从后往前
如果目标可以reach，把目标点移到当前点
*/

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

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int height = 0;
        for (int i=nums.size()-2; i>=0; i--) {
            if (height >= nums[i]) height++;
            else height = 0;
        }
        return height == 0;
    }
};

//width 只有当 nums[i] 等于0时，才会从0 变成1;，因为是从后向前的顺序，只要nums[i] 能跨过这个width时，width又变成0
//比如 [3,3,1,0], 当i = 1,时， width = 2, 但是nums[i] > width, 跨过到达0之前，
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int width = 0;
        for (int i=nums.size()-2; i>=0; i--) {
            if (width >= nums[i]) width++;
            else width = 0;
        }
        return width == 0;
    }
};

