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



//把所有的情况都列出来了, balance 初始化时size, 最大值是 2size, 最小值是 0,
int findMaxLength(vector<int>& nums) {
    int size = nums.size(), ballance = size, max_len = 0;
    int ballances[size * 2 + 1] = {};
    for (auto i = 0; i < size; ++i) {
        ballance += nums[i] == 0 ? -1 : 1;
        if (ballance == size) max_len = i + 1;
        else {
            if (ballances[ballance] != 0) max_len = max(max_len, i - ballances[ballance] + 1);
            else ballances[ballance] = i + 1;
        }
    }
    return max_len;
}
