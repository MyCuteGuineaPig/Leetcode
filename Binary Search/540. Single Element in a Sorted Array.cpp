/*
540. Single Element in a Sorted Array

Given a sorted array consisting of only integers where every element appears twice except for one element which appears once. Find this single element that appears only once.

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10
Note: Your solution should run in O(log n) time and O(1) space.



*/


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            int mid = l + (r-l)/2;
            if(!(mid&1)) mid++;
            if(nums[mid]!=nums[mid-1]) r = mid-2;
            else l = mid+1;
        }
        return nums[l];
    }
};



class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            int mid = l + (r-l)/2;
            if(mid&1) mid--;
            // We didn't find a pair. The single element must be on the left.
            // (pipes mean start & end)
            // Example: |0 1 1 3 3 6 6|
            //               ^ ^
            // Next:    |0 1 1|3 3 6 6
            if(nums[mid]!=nums[mid+1])
                r = mid;

            // We found a pair. The single element must be on the right.
            // Example: |1 1 3 3 5 6 6|
            //               ^ ^
            // Next:     1 1 3 3|5 6 6|
            else l = mid+2;
        }
        return nums[l];
    }
};



class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            int mid = (l + r) >> 1;
            if (nums[mid] == nums[mid ^ 1]) //mid 是奇数, mid ^ 1 = mid - 1
                                            //mid 是偶数, mid ^ 1 = mid + 1
                l = mid + 1;
            else
                r = mid;
        }
        return nums[l];
    }
};



class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size(), lo=0, hi=n/2;
        while (lo < hi) {
            int m = (lo + hi) / 2;
            if (nums[2*m]!=nums[2*m+1]) hi = m;
            else lo = m+1;
        }
        return nums[2*lo];
    }
};


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int N = nums.size();
        if(N == 1)
            return nums[0];
        
        int left = 0;
        int right = N - 1;
        int mid;
        
        while(left < right){
            mid = left + ((right  - left) >> 1);
            if(nums[mid] == nums[mid + 1]){
                // from index mid to (N - 1) - if even then check left interval
                if(mid % 2 == 0)
                  left = mid + 2;
                else
                   right = mid - 1;
            }else if(nums[mid] == nums[mid - 1]){
                // from index (mid - 1) to (N - 1) - if even then check left interval
                if(mid % 2 == 0)
                    right = mid - 2;
                else
                    left = mid + 1;
            }else
                return nums[mid];
        }
        
        return nums[left];
    }
};


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi){
            int mid = 2 * ((lo + hi) / 4);
            if(nums[mid] == nums[mid+1])
                lo = mid+2;
            else
                hi = mid;
        }
	    return nums[lo];
    }
};