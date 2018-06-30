/*
561. Array Partition I
Given an array of 2n integers, your task is to group these integers into n pairs of integer, 
say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].


*/


class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int res = 0;
        for(int i = 0; i<nums.size(); i+=2)
            res += nums[i];
        return res;
    }
};


class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        const int left = -10000;
        const int right = 10000;
        vector<int>bucket(right-left+1);
        for(int i: nums)
            bucket[i+right]++;
        int res = 0, r = 0;
        for(int i = 0; i<bucket.size(); i++)
        {
            res += (bucket[i] - r+1)/2*(i-right); 
            //((bucket[i] + right - r)) 有多少个，比如bucket[i]=3，到bucket[i]是偶数(偶数是根据nums[i]排序第2n个)，我们需要偶数个加上两个i，如果到bucket[i]是奇数数，我们需要偶数个加上一个i
            r = (bucket[i]+r) % 2 ;
        }
        return res;
    }
};


class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        array<int, 20001> buckets{0};
        for(auto num : nums) {
            ++buckets[num + 10000];
        }
        
        int sum = 0, count = 0, idx = 0;
        while(count < nums.size()) {
            if(buckets[idx]==0) {
                idx++;
            }
            else {
                if((count % 2) == 0) 
                    sum += (idx - 10000);
                --buckets[idx];
                ++count;
            }
        }
        return sum;
    }
};



