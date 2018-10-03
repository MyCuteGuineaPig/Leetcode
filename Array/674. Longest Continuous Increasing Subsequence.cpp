/*
674. Longest Continuous Increasing Subsequence

Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

Example 1:
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4. 
Example 2:
Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length is 1. 
Note: Length of the array will not exceed 10,000.

*/

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        int res = 0, prev = nums[0], cur = 0;
        for(auto i: nums){
            if(i>prev) cur ++;
            else cur = 1;
            res = max(res, cur);
            prev = i;
        }
        return res;
    }
};

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size()<2) return nums.size();
        int res = 0, curr=1;
        for(int i = 1; i<nums.size(); i++){
            if(nums[i]>nums[i-1]){
                curr++;
            }
            else{
                res = max(res, curr);
                curr = 1;
            }
        }
        res = max(res, curr);
        return res;
    }
};

class Solution {
public:
    int findLengthOfLCIS(vector<int>& a) {
        int mx = 0, len = 0;
        for (int i = 0; i < a.size(); i++) {
            if (i == 0 || a[i] <= a[i - 1]) len = 0;
            mx = max(mx, ++len);
        }
        return mx;
    }
};


//Two Pointer
class Solution {
public:
    int findLengthOfLCIS(vector<int>& a) {
        int mx = 0;
        for (int i = 0, j = 0; j < a.size(); j++) {
            if (j == 0 || a[j] <= a[j - 1]) i = j;
            mx = max(mx, j - (i - 1))
        }
        return mx;
    }
};