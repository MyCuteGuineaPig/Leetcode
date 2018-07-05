/*
268. Missing Number

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

*/

/*
通过修改nums为负
two pass 
如果当前 nums[i] = n, 不修改
如果nums[index] = 0, 0因为无法判断正负，就给nums[index] assign -(n + 1)
*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(auto i: nums){
            if(i<n){
                int index =  max(i, -i);
                if(index > n) index = 0;
                if(nums[index]!=0)
                    nums[index] = min(nums[index], -nums[index]); 
                else 
                    nums[index] = -(n+1);
            }
        }
        for(int i = 0; i<nums.size();i++)
            if(nums[i]>=0) //比如[2,0]
                n = i;
        return n;
    }
};

/*

One pass： 因为nums中每个数都是在[0,n]中，
所以把nums[i]每个数 ^ i (i = [0,n]), 如果i出现在nums[i], 会消掉，如果没出现，就得出最终结果
*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xorr = 0;
        for(int i = 0; i<nums.size();i++){
            xorr = xorr ^ i ^ nums[i];
        }
        return xorr^nums.size();
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            res ^= (i + 1) ^ nums[i];
        }
        return res;
    }
};

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    vector<int> expected(nums.size()); 
    iota(expected.begin(), expected.end(), 1);  // Costs extra space O(n)
    return accumulate(nums.cbegin(), nums.cend(), 0, bit_xor<int>()) ^
           accumulate(expected.cbegin(), expected.cend(), 0, bit_xor<int>());
  }
};

/*
Math solution
*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (auto n : nums) {
            sum += n;
        }
        return (n + 1) * n / 2 - sum;
    }
};


//避免overflow，如果都出现 (1+n)*n/2 - sum = 0; 
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sum += nums[i] - i;
        return nums.size() - sum;
    }
};
