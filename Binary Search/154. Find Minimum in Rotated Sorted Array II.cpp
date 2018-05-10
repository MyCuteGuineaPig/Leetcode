/*
154. Find Minimum in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

Example 1:

Input: [1,3,5]
Output: 1
Example 2:

Input: [2,2,2,0,1]
Output: 0
Note:

This is a follow up for "Find Minimum in Rotated Sorted Array".
Would allow duplicates affect the run-time complexity? How and why?

*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            while(l<r && nums[l+1] == nums[l]) l++;
            while(l<r && nums[r-1] == nums[r]) r--;
            int mid = l + (r-l)/2;
            if(nums[mid]>nums[r]) l = mid+1; //turn on right
            else if(nums[mid]<nums[l]) r = mid; //turn on left
            else break;
        }
        return nums[l];
    }
};



class Solution {
public:
    int findMin(vector<int> &num) {
        int lo = 0;
        int hi = num.size() - 1;
        int mid = 0;
        
        while(lo < hi) {
            mid = lo + (hi - lo) / 2;
            
            if (num[mid] > num[hi]) {
                lo = mid + 1;
            }
            else if (num[mid] < num[hi]) {
                hi = mid;
            }
            else { // when num[mid] and num[hi] are same
                hi--;
            }
        }
        return num[lo];
    }
};

/*
The idea to solve this problem is still to use invariants. We set l to be the left pointer and r to be the right pointer. Since duplicates exist, the invatiant is nums[l] >= nums[r] (if it does not hold, then nums[l] will simply be the minimum). We then begin binary search by comparing nums[l], nums[r] with nums[mid].

If nums[l] = nums[r] = nums[mid], simply apply linear search within nums[l..r].
If nums[mid] <= nums[r], then the mininum cannot appear right to mid, so set r = mid;
If nums[mid] > nums[r], then mid is in the first larger half and r is in the second smaller half,
     so the minimum is to the right of mid: set l = mid + 1.

*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (nums[l] >= nums[r]) {
            int mid = (l & r) + ((l ^ r) >> 1);
            if (nums[l] == nums[r] && nums[mid] == nums[l])
                return findMinLinear(nums, l, r);
            if (nums[mid] <= nums[r]) r = mid; //no turn on right
            else l = mid + 1;
        }
        return nums[l];
    } 
private:
    int findMinLinear(vector<int>& nums, int l, int r) {
        int minnum = nums[l];
        for (int p = l + 1; p <= r; p++)
            minnum = min(minnum, nums[p]);
        return minnum;
    }
};


class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (nums[l] >= nums[r]) {
            int mid = (l & r) + ((l ^ r) >> 1);
            //cout<<" left "<<l<<" mid "<<mid<<" right "<<r<<endl;
            if (nums[l] == nums[r] && nums[mid] == nums[l])
                return findMinLinear(nums, l, r);
            if (nums[mid] > nums[r])  l = mid + 1;  //turn is on right
            else r = mid;
        }
        return nums[l];
    } 
private:
    int findMinLinear(vector<int>& nums, int l, int r) {
        int minnum = nums[l];
        for (int p = l + 1; p <= r; p++)
            minnum = min(minnum, nums[p]);
        return minnum;
    }
};