/*
81. Search in Rotated Sorted Array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

You are given a target value to search. If found in the array return true, otherwise return false.

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
Follow up:

This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
Would this affect the run-time complexity? How and why?


*/


class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            while(r>l && nums[l]==nums[l+1]) l++; 
            while(r>l && nums[r]==nums[r-1]) r--;

            if(nums[mid] == target) return true;
            if(target>nums[mid]){
                if( nums[mid]<nums[l] && nums[l]<=target){
                    r = mid-1;
                }
                else 
                    l = mid+1;
            }else{
                if(nums[mid]>nums[r] && nums[r]>=target)
                    l = mid + 1;
                else r = mid-1;
            }
        }
        return false;
    }
};
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            while(r>l && nums[l]==nums[l+1]) l++;// skip duplicates from the left
            while(r>l && nums[r]==nums[r-1]) r--; // skip duplicates from the right
            int mid = l + (r-l)/2;
            
            if(nums[mid] == target) return true;
            if(target>nums[mid]){
                if( nums[l]>nums[mid] && nums[l]<=target)
                   r = mid-1;
                else 
                    l = mid+1;
            }else{
                if(nums[r]<nums[mid] && nums[r]>=target)
                    l = mid + 1;
                else r = mid-1;
            }
        }
        return false;
    }
};




/*
The idea is the same as the previous one without duplicates

1) everytime check if targe == nums[mid], if so, we find it.
2) otherwise, we check if the first half is in order (i.e. nums[left]<=nums[mid]) 
  and if so, go to step 3), otherwise, the second half is in order,   go to step 4)
3) check if target in the range of [left, mid-1] (i.e. nums[left]<=target < nums[mid]), 
  if so, do search in the first half, i.e. right = mid-1; otherwise, search in the second half left = mid+1;
4)  check if target in the range of [mid+1, right] (i.e. nums[mid]<target <= nums[right]),
    if so, do search in the second half, i.e. left = mid+1; otherwise search in the first half right = mid-1;
    The only difference is that due to the existence of duplicates, we can have nums[left] == nums[mid] 
    and in that case, the first half could be out of order (i.e. NOT in the ascending order, e.g. [3 1 2 3 3 3 3]) 
    and we have to deal this case separately. 
    In that case, it is guaranteed that nums[right] also equals to nums[mid], 
    so what we can do is to check if nums[mid]== nums[left] == nums[right] before the original logic, 
    and if so, we can move left and right both towards the middle by 1. and repeat.
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right =  nums.size()-1, mid;
        
        while(left<=right)
        {
            mid = (left + right) >> 1;
            if(nums[mid] == target) return true;

            // the only difference from the first one, trickly case, just updat left and right
            if( (nums[left] == nums[mid]) && (nums[right] == nums[mid]) ) {++left; --right;}

            else if(nums[left] <= nums[mid])
            {
                if( (nums[left]<=target) && (nums[mid] > target) ) right = mid-1;
                else left = mid + 1; 
            }
            else
            {
                if((nums[mid] < target) &&  (nums[right] >= target) ) left = mid+1;
                else right = mid-1;
            }
        }
        return false;
    }
};

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            while(r>l && nums[l]==nums[l+1]) l++;
            while(r>l && nums[r]==nums[r-1]) r--;
            int mid = l + (r-l)/2;
            //cout<<" left "<<l<<" r "<<r<<" mid "<<mid<<endl;
            
            if(nums[mid] == target) return true;
            if(target>nums[mid]){
                if(l==mid || nums[l]<nums[mid] || nums[l]>target) l = mid+1; 
                /*nums[l]<nums[mid] means no turn from l to mid, 
                 nums[l]>target means even there is a turn, cannot in left side, nums[l]>nums[mid] && nums[l]>target,
                 l = mid, no way to do left
                */
                else r = mid-1;
            }else{
                if(nums[r]>nums[mid] || nums[r]<target) r = mid-1;
                /*
                nums[r]>nums[mid] means no turn from mid to r, 
                nums[r]<target means even there is a turn, cannot in right side
                 l = mid, no way to do left
                */
                else l = mid + 1;
            }
            
            //cout<<" after "<<l<<" r "<<r<<" mid "<<mid<<endl;
        }
        return false;
    }
};



class Solution {
public:
  bool search(int A[], int n, int target) {
    int lo =0, hi = n-1;
    int mid = 0;
    while(lo<hi){
          mid=(lo+hi)/2;
          if(A[mid]==target) return true;
          if(A[mid]>A[hi]){
              if(A[mid]>target && A[lo] <= target) hi = mid;
              else lo = mid + 1;
          }else if(A[mid] < A[hi]){
              if(A[mid]<target && A[hi] >= target) lo = mid + 1;
              else hi = mid;
          }else{
              hi--;
          }
          
    }
    return A[lo] == target ? true : false;
  }
};



class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right =  nums.size()-1, mid;
        
        while(left<=right)
        {
            mid = (left + right) >> 1;
            if(nums[mid] == target) return true;

            // the only difference from the first one, trickly case, just updat left and right
            if( (nums[left] == nums[mid]) && (nums[right] == nums[mid]) ) {++left; --right;}

            else if(nums[left] <= nums[mid])
            {
                if( (nums[left]<=target) && (nums[mid] > target) ) right = mid-1;
                else left = mid + 1; 
            }
            else
            {
                if((nums[mid] < target) &&  (nums[right] >= target) ) left = mid+1;
                else right = mid-1;
            }
        }
        return false;
    }
};