/*

15. 3Sum


Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

*/


/*
先sort + 两个pointers
[-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0]

-5, -5, -4, -4, -4, -2, -2, -2, 0, 0, 0, 1, 1, 3, 4, 4
sort 好处是避免重复, 还有通过sort，可以建一个头尾的pointer, a = nums[i] 固定的， b+c 和-a比，来调整两个pointers 位置


返回值：
[[-5,1,4],[-4,0,4],[-4,1,3],[-2,-2,4],[-2,1,1],[0,0,0]]

不能跳过所有重复的，如果跳过所有重复的比如[-2,1,1], [0,0,0]就不能返回
一个好的方法是，对比现在和上一个位置，如果一样的话，不进行比较先跳过，

比如现在是
    -2, 0, 0, 0, 1, 1, 3, 4, 4
    a   b                    c  > 0
    a   b               c       > 0
    a   b            c          > 0 
    a            b   c          = 0


*/

//先跳再比较, 但初始j（j = i+1）,k (k == size - 1) 时不跳
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>res;
        sort(nums.begin(), nums.end());
        for(int i = 0; nums.size() > 2 && i<nums.size()-2 && nums[i] <=0;i++){ //条件nums[i] <= 0， Y因为是sort 大于0肯定没结果
            if(i>0 && nums[i] == nums[i-1]) continue;//cannont make the first as same, control the first
            //like -1, -1 , 0 is allowed, but next time nums[i] cannot as -1
            for(int j = i+1, k = nums.size()-1; j<k;){
                if(j>i+1 && nums[j] == nums[j-1]) j++; //skip duplicate
                else if(k < nums.size()-1 && nums[k] == nums[k+1]) k--;//skip duplicate
                else if(nums[j]+nums[k] + nums[i] < 0) j++;
                else if(nums[j]+nums[k] + nums[i] > 0) k--;
                else res.push_back({nums[i], nums[j++], nums[k--]});
            }
        }
        
        return res;
    }
};

//先比较，然后跳过重复的
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>>res;
        sort(nums.begin(), nums.end());
        for(int i = 0; nums.size() > 2 && i<nums.size()-2;i++){
            int j = i+1, k = nums.size()-1;
            while(j < k){
                if( nums[i] + nums[j] + nums[k] == 0){
                    res.push_back({nums[i], nums[j], nums[k]});
                    while(j<k && nums[j] == nums[j+1]) j++;
                    while(j<k && nums[k] == nums[k-1]) k++;
                    j++; k--;
                }
                else if(nums[i] + nums[j] + nums[k] < 0){
                    while(j<k && nums[j] == nums[j+1]) j++;
                    j++;
                }else{
                    while(j<k && nums[k] == nums[k-1]) k--;
                    k--;
                }
            }
            while(i+1<nums.size() && nums[i] == nums[i+1]) i++;
        }
        
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (unsigned int i=0; i<nums.size(); i++) {
            if ((i>0) && (nums[i]==nums[i-1]))
                continue;
            int l = i+1, r = nums.size()-1;
            while (l<r) {
                int s = nums[i]+nums[l]+nums[r];
                if (s>0) r--;
                else if (s<0) l++;
                else {
                    res.push_back(vector<int> {nums[i], nums[l], nums[r]});
                    while (nums[l]==nums[l+1]) l++;
                    while (nums[r]==nums[r-1]) r--;
                    l++; r--;
                }
            }
        }
        return res;
    }
};