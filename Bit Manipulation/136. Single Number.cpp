/*
136. Single Number

Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4


*/

/*

For anyone who didn't understood why this works here is an explanation. 
This XOR operation works because it's like XORing all the numbers by itself. 
So if the array is {2,1,4,5,2,4,1} then it will be like we are performing this operation

((2^2)^(1^1)^(4^4)^(5)) => (0^0^0^5) => 5.

Hence picking the odd one out ( 5 in this case).
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int x = 0;
        for(auto i: nums)
            x ^= i;
        return x;
    }
};