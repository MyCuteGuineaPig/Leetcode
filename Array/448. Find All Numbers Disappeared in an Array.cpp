/*
448. Find All Numbers Disappeared in an Array



Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]

*/


/*

Trick: flip elements to negative on index (nums[i]-1)

第二次pass 如果nums[i]为正，代表上一个pass 没有flip，代表miss i+1

*/
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int>res;
        for(int i = 0; i<nums.size();i++){
            int index = abs(nums[i]) - 1;
            nums[index] = -abs(nums[index]);
        }
        for(int i = 0; i<nums.size();i++){
            if(nums[i]>0) res.push_back(i+1);
        }
        return res;
    }
};



/*
Trick II:  第一次pass，把nums[i] 放在nums[i] - 1的位置上； 第二次pass 如果第i的element 不是nums[i]-1就是重复的

*/

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int>res;
        for(int i = 0; i<nums.size();){
            int index = nums[i] - 1;
            if(nums[index] != nums[i]) 
                swap(nums[index], nums[i]);
            else i++;
        }
        for(int i = 0; i<nums.size();i++){
            if(nums[i]!=i+1) res.push_back(i+1);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;
        for(int i=0;i<nums.size();i++)
        {
            while(nums[i]!=nums[nums[i]-1]) swap(nums[i],nums[nums[i]-1]);
        }
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]!=i+1) result.push_back(i+1);
        }
        return result;
    }
};