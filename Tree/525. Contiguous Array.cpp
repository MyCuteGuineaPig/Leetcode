/*
525. Contiguous Array

Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.


*/


/*

把所有的0变成-1， 所以当有sum[i,j] = 0时，知道现在有 同等的1 和 0

Also put the sum to index mapping to a HashMap to make search faster.
*/


class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int>map;
        map[0] = -1;
        int sum = 0, res = 0;
        for(int i = 0; i<nums.size(); i++){
            sum += nums[i] == 0 ? -1: 1;
            if(map.count(sum))
                res = max(res, i - map[sum]);
            else map[sum] = i;
        }
        return res;
    }
};

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
    const size_t len = nums.size();
    if (len < 2) return 0;
    if (len == 2 && nums[1] + nums[0] == 1) return 2;

    int sum = len, ret = 0;
    // -len -> 0; 0 -> len; len -> len * 2
    vector<int> sumToIndexVec(2 * len + 1, -1);
    // sumToIndexVec[len] = -1;

    for (int i = 0; i < len; ++i) {
        sum += nums[i] == 0 ? -1 : 1;
        if (sum == len || sumToIndexVec[sum] != -1) 
            ret = max(ret, i - sumToIndexVec[sum]);
        else sumToIndexVec[sum] = i;
    }

    return ret;
    }
};