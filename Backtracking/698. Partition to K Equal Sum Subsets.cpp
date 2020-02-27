/*
698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether
 it's possible to divide this array into k non-empty subsets whose sums are all equal.

Example 1:
Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.


*/

//BackTrack with loop buckets
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if( sum % k != 0) 
            return false;
        int avg = sum / k;
        for(auto i: nums) 
            if(i > avg)
                return false;
        sort(nums.begin(), nums.end(), greater<int>()); //需要sort 不sort 会TLE
        vector<int>buckets(k, avg);
        return backTrack(nums, k, 0, buckets);
    }

    bool backTrack(vector<int>&nums, const int& k, int start, vector<int>&buckets){
        if(start == nums.size()) 
            return true;

        for(int i = 0; i < k; ++i)
        {
            if(buckets[i] >= nums[start])
            {
                buckets[i] -= nums[start];
                if (backTrack(nums, k, start +1, buckets))
                    return true;
                buckets[i] += nums[start];
            }
        }
        return false;
    }
};


//BackTrack with loop nums
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for_each(nums.begin(),nums.end(),[&](int a){sum+= a;});
        if(sum%k) return false;
        sum /= k;
        sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        return backtrack(nums,k, 0,sum,sum);
    }
    
    bool backtrack(vector<int>& nums, int k, int begin,int rem, const int & sum){
        if(rem == 0){
            k--;
            rem = sum;
        }
        if(k == 0) 
            return true;
        for(int i = begin; i<nums.size(); i++){
            if(nums[i]<=rem){
                swap(nums[i],nums[begin]);
                if(backtrack(nums,k,begin+1,rem-nums[begin],sum)) return true;
                swap(nums[i],nums[begin]);
            }
            if(nums[i]>sum) return false;
        }
        return false;
    }
};




class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for_each(nums.begin(),nums.end(),[&](int a){sum+= a;});
        if(sum%k) return false;
        sum /= k;
        //sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        return backtrack(nums,k,0,sum,sum);
    }
    
    bool backtrack(vector<int>& nums, int k, int begin, int rem, const int & sum){
        if(rem == 0)
            return backtrack(nums,k-1, 0, sum, sum);
        if(k == 0) 
            return true;
        for(int i = begin; i<nums.size(); i++){
            if(nums[i]>0 && nums[i]<=rem){
                nums[i] *= -1;
                if(backtrack(nums,k, i+1, rem+nums[i], sum)) return true;
                nums[i] *= -1;
            }
            if(nums[i]>sum) return false;
        }
        return false;
    }
};
