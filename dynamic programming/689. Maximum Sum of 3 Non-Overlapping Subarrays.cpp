/*
689. Maximum Sum of 3 Non-Overlapping Subarrays

In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

Example:
Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Note:
nums.length will be between 1 and 20000.
nums[i] will be between 1 and 65535.
k will be between 1 and floor(nums.length / 3).

*/



class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        vector<int>W(nums.size()-k+1, 0);
        vector<int>left(nums.size()-k+1, 0);
        vector<int>right(nums.size()-k+1, 0);
        int best = 0;
        for(int i = 0, cur = 0; i<nums.size(); i++){
            cur += nums[i];
            if(i>=k)
                cur -= nums[i-k];
            if(i>=k-1){
                W[i-k+1] = cur;
                if(W[i-k+1]>W[best])
                    best = i-k+1;
                left[i-k+1] = best;
            }
        }
        best = nums.size()-k;
        for(int i = nums.size()-k; i>=0; i--){
            if(W[i]>=W[best])
                best = i;
            right[i] = best;
        }
        vector<int>res={0, k, 2*k};
        for(int i = k; i<=nums.size()-2*k; i++){
            if(W[left[i-k]]+W[i]+ W[right[i+k]] > W[res[0]] + W[res[1]] + W[res[2]])
                res = {left[i-k], i, right[i+k]};
        }
        return res;
    }
};


/*

            7   13   20   19   19   2   10   1   1   19
    W       40  52   58   40   31   13  12   21 
    left    0   1    2    2    2    2   2    2 
    right   2   2    2    3    4    7   7    7 

*/