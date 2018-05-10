/*
162. Find Peak Element

A peak element is an element that is greater than its neighbors.

Given an input array nums, where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 
Explanation: Your function can return either index number 1 where the peak element is 2, 
             or index number 5 where the peak element is 6.
Note: Your solution should be in logarithmic complexity.

*/


class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        while(low<high){
            int mid = low + (high-low)/2;
            int mid2 = mid+1;
            if(nums[mid]<nums[mid2])
                low = mid2;
            else
                high = mid;
        }
        return low;
    }
};


class Solution {
public:
    int findPeakElement(const vector<int> &num) 
    {
        return helper(num,0,num.size()-1);
    }
    
    int helper(const vector<int> &num, int low, int high){
        if(low>=high) return low;
        int mid1 = (low+high)/2;
        int mid2 = mid1+1;
        //cout<<" low "<<low<<" high "<<high <<" mid1 "<<mid1<<" mid2 "<<mid2<<endl;
        if(num[mid1] < num[mid2])
            return helper(num,mid2,high);
        else
            return helper(num,low,mid1);
    }
};


