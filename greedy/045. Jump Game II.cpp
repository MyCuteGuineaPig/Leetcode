/*
45. Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)


*/



/*

在现有可以jump 的区域里，找这一步加上下一步可以跳的最远的
这一步到 reach，下一步到next = reach + nums[reach]， ind表示可以跳的最远的index


    [2,3,1,1,4]
比如现在 i = 0, reach = 2, next = reach + nums[reach] = 2 + 1 = 3
        但是发现从0到2中, j = 1时  j + nums[j] = 3 + 1 = 4 > next = 3; 所以跳到1 再跳3会更远
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size() <= 1) return 0;
        int count = 0, i = 0;
        while(i < nums.size()-1){
            count++;
            if(i + nums[i] >= nums.size() - 1) break;
            
            int reach = i+nums[i], next = reach + nums[reach], ind = i+ nums[i];
            for(int j = i; j<reach; j++){
                if(j+nums[j] > next){
                    next = j + nums[j];
                    ind = j;
                }
            }
            
            i = ind;
        }
        return count;
    }
};


/*

与上面解一样的道理，找目前可以跳的范围内(这一跳加上下一跳)最远的点,curfastest, 
当到之前设定的点currend时，更新最远点为 curend 为curfast

*/
class Solution {
public:
    int jump(vector<int>& nums) {
        int jump = 0, curfarthest = 0, curend = 0;
        for(int i = 0; i<nums.size() && curend<nums.size()-1;i++){ //需要的是curend < nums.size()-1
        /*
            不能是curfast < nums.size()-1，可能出现还没update, 就结束了
            比如[2,3,1,1,4], 在一点，curfast = 1 + 3 = 4, 下一次loop 停止在最后一点
            但是curend 在2点
        */
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