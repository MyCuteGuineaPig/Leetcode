/*
560. Subarray Sum Equals K

Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
Note:
The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

*/

/*
用hashmap表示前面数的和（0,j)，有几个， 那么只需要找(0,i)的sum - k在不在map中，在的话， res += map[sum-k] (可能一个sum出现很多遍)
we just need to go through the array, calculate the current sum and save number of all seen PreSum to a HashMap. 
Time complexity O(n), Space complexity O(n).
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0, res = 0;
        unordered_map<int,int>map = {{0,1}}; //to aviod like nums = [0], k = 0
        for(auto i: nums){
            sum += i;
            if(map.find(sum-k) != map.end()) res+=map[sum-k];
            map[sum]++;
        }
        return res;
    }
};