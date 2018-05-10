/*
153. Find Minimum in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2] 
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0


*/


class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            int mid = l + (r-l)/2;
            //cout<<" mid "<<mid<<" l "<<l<<" r "<<r<<endl;
            if(nums[mid]>nums[r]) //turn is on right 5,6,7,8,0,1,2   mid = 8, left = 5, right =2
                l = mid+1;
            else if(nums[mid]<nums[l]) //turn is on left 5,6,0,1,2,3,4  mid = 1, left = 5, right =4
                r = mid;  
                /*
                此题不能用mid -1 ， 因为nums[mid] < nums[l] nums[mid] 可能是最小的解，但是mid-1，left,right都在解的左侧，
                比如 [5,6,0,1] left = 5, right = 0, 0<5, left = 5, right = 6
                但是还有个问题，下次比较在left,right区间里面有没有turn是在【5，6】,就忽略了最优解 

                */
            else break;
        }
        return nums[l];
    }
};


class Solution {
public:
    int findMin(vector<int>& nums) {
        int start=0,end=nums.size()-1;
        
        while (start<end) {
            if (nums[start]<nums[end]) // not rotated.
                return nums[start];
            int mid = (start+end)/2;

            if (nums[mid]>=nums[start]) {// mid falls in ascending.
                start = mid+1;
            } else {
                end = mid; // min on left.
            }
        }
        
        return nums[start];
    }
};