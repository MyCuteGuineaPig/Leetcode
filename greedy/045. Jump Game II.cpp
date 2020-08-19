
/*

在现有可以jump 的区域里，找这一步 + 下一步可以跳的最远的
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

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return 0;
	    int level=0,currentMax=0,i=0,nextMax=0;

         while(i <= currentMax){		//nodes count of current level>0
             level++;
             for(;i<=currentMax;i++){	//traverse current level , and update the max reach of next level
                nextMax=max(nextMax,nums[i]+i);
                if(nextMax>=n-1)return level;   // if last element is in level+1,  then the min jump=level 
             }
             currentMax=nextMax;
         }
         return 0;
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
class Solution {
public:
    int jump(vector<int>& nums) {
        int jump = 0, curfarthest = 0, curend = 0;
        for(int i = 0; i<nums.size() && curend<nums.size()-1;i++){ //需要的是curend < nums.size()-1
            if(i > curend){
                jump++;
                curend = curfarthest;
            }
            curfarthest = max(curfarthest,i+nums[i]);
        }
        return jump;
    }
};


//2020
class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size()==1) return 0;
        int far = 0, steps = 0, prev = 0;
        for(int i = 0; i < nums.size()-1; ++i){
            if(i >= prev){
                prev = max(far,i+nums[i]);
                ++steps;
            }
            far = max(far, i+nums[i]);
        }
        return steps;
    }
};