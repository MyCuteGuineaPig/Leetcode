/*
35. Search Insert Position

Given a sorted array and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Example 1:

Input: [1,3,5,6], 5
Output: 2
Example 2:

Input: [1,3,5,6], 2
Output: 1
Example 3:

Input: [1,3,5,6], 7
Output: 4
Example 4:

Input: [1,3,5,6], 0
Output: 0
*/



class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while(left<right){
            int mid = left+(right-left)/2;
            /*


            比如[1,3,5,6], target = 5, 
            mid = 2, left = 0, right = 4 (num[mid]=5 >= target right = 2)
            mid = 1 ,left = 0, right = 2  (nums[mid] = 3 < target], left = mid+1 = 2 )
            
            */

            if(nums[mid]>=target)
                right = mid;
            else left = mid+1;
        }
        return left;
    }
};


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left+(right-left)/2;
            //cout<<" mid "<<mid<<" left "<<left<<" right "<<right<<endl;
            if(nums[mid]>=target)  
            /*
            因为要返回left，所以只要mid>=target, right = mid-1,不用管right, 
            Case1; 可能有这种情况，比如【2，3】, target = 3, left在2上，right在3上，mid在2上, left=mid+1, 
                                第二步，left 在3， right 在3，mid在3， 把right--就可以


            比如[1,3,5,6], target = 5, 
            mid = 1, left = 0, right = 3 (num[mid]<t left = mid+1 = 2)
            mid = 2 ,left = 2, right = 3  (nums[mid] >=target, right = mid-1 = 2 )
             mid = 2 ,left = 2, right = 2(nums[mid] >=target, right = mid-1 =1 )
 
            比如[1,3,5,6], target = 2, 
            mid = 1, left = 0, right = 3 (num[mid]>=target r = mid-1 = 0)
            mid = 0,left = 0, right = 0  (nums[mid] < target, left = mid+1 = 1 )
 
            if(nums[mid]>=target)  有可能nums[mid]==target,right 向左动了，
                right = mid-1;  
            所以等下一个left = right时候，把left + 1, 再移回来

            而上面答案，保证right 不会多移动，
            if(nums[mid]>=target)
                right = mid;
            所以while条件不需要left<=right, 只要left<right  
            当right - left = 1时， mid =left, 如果nums[left]>=target, right=mid=left
            否则 left = mid+1 = right
            
            */
                right = mid-1;  
            else left = mid+1;
        }
        return left;
    }
};


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {    
        return lower_bound(nums,target);
    }
    
    int lower_bound(vector<int>& nums,int target){
        int low=0,high=nums.size()-1;
        
        while(low<=high){
            int mid=(low+high)>>1;
            if(nums[mid]<target)
                low=mid+1;
            else 
                high=mid-1;
        }
        return low;
    }
};


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums.begin(),nums.end(),target) - nums.begin();
    }
};