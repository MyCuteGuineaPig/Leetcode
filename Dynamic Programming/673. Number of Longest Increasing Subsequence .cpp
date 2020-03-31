/*
673. Number of Longest Increasing Subsequence

Given an unsorted array of integers, find the number of longest increasing subsequence.

Example 1:
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
Example 2:
Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.



*/

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int>maxLen(nums.size(),1);
        vector<int>cnt(nums.size(),1);
        int curmaxLen = 0, res = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]>nums[j] && maxLen[j]+1>maxLen[i]){
                    maxLen[i] =  maxLen[j]+1;
                    cnt[i] = cnt[j];
                }
                else if(nums[i]>nums[j] && maxLen[j]+1 == maxLen[i]){
                    cnt[i]+=cnt[j];
                }
            }
            if(curmaxLen < maxLen[i]){
                curmaxLen = maxLen[i];
                res = cnt[i];
            }else if(curmaxLen ==  maxLen[i])
                res += cnt[i];
        }
        return res;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int>maxLen(nums.size(),1);
        vector<int>cnt(nums.size(),1);
        int curmaxLen = 0, res = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]>nums[j] && maxLen[j]+1>maxLen[i]){
                    maxLen[i] =  maxLen[j]+1;
                    cnt[i] = cnt[j];
                }
                else if(nums[i]>nums[j] && maxLen[j]+1 == maxLen[i]){
                    cnt[i]+=cnt[j];
                }
            }
            curmaxLen = max(curmaxLen,maxLen[i]);
        }
        for(int i = 0; i<nums.size();i++){
            if(maxLen[i] == curmaxLen)
                res+=cnt[i];
        }
        return res;
    }
};