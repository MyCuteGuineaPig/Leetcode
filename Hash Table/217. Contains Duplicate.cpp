/*
217. Contains Duplicate

Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true
Example 2:

Input: [1,2,3,4]
Output: false
Example 3:

Input: [1,1,1,3,3,4,3,2,4,2]
Output: true
*/


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>set;
        for(auto i: nums)
            if(set.count(i)) return true;
            else set.insert(i);
        return false;
    }
};


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> nums_set(nums.begin(), nums.end());
        return nums_set.size() != nums.size();
    }
};


// Time:  O(nlogn)
// Space: O(1)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return unique(nums.begin(), nums.end()) != nums.end();
    }
};