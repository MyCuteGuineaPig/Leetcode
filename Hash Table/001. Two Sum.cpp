/*
1. Two Sum

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].


*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>m;
        for(int i = 0; i<nums.size();i++){
            if(m.count(target-nums[i]))  return {m[target-nums[i]],i};
            m[nums[i]] = i;
        }
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashTable;
        for(int i=0; i<nums.size();; i++) {
            int complement = target - nums[i];
            auto found = hashTable.find(complement);
            if(found == hashTable.end()) {
                hashTable.insert(pair<int, int>{nums[i], i});
            } else {
                return vector<int>{found->second, i};
            }
        }
    }