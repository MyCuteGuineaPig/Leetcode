/*
169. Majority Element


Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2


*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0, res = 0;
        for(auto i: nums)
        {
            if(res!=i && --count < 0) { res = i; count = 0;}
            else if(res == i) count ++;
        }
        return res;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, major = 0;
        for (int &n : nums) {
            if (cnt == 0) 
                major = n;
            if (major != n)
                cnt --;
            else
                cnt ++;
        }
        return major;
    }
};

/*

This is a really nice idea and works pretty well (16ms running time on the OJ, 
almost fastest among the C++ solutions). The proof is already given in the suggested solutions.

The code is as follows, randomly pick an element and see if it is the majority one.

*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        srand(unsigned(time(NULL)));
        while (true) {
            int idx = rand() % n;
            int candidate = nums[idx];
            int counts = 0; 
            for (int i = 0; i < n; i++)
                if (nums[i] == candidate)
                    counts++; 
            if (counts > n / 2) return candidate;
        }
    }
};

/*

算每一bit位是不是有大于n/2个是1 break，如果有设1，如果没有继续
Bit Manipulation

Another nice idea! The key lies in how to count the number of 1's on a specific bit. 
Specifically, you need a mask with a 1 on the i-the bit and 0 otherwise to get the i-th bit of each element in nums. 

*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = 0, n = nums.size();
        for (int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
            int bitCounts = 0;
            for (int j = 0; j < n; j++) {
                if (nums[j] & mask) bitCounts++;
                if (bitCounts > n / 2) {
                    major |= mask;
                    break;
                }
            }
        } 
        return major;
    } 
};