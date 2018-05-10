/*
33. Search in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

*/



class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            int mid = l + (r-l)/2;
            if(target == nums[mid]) return mid;
            if(target>nums[mid]){//  
                if(nums[l]>nums[mid] && nums[l]<=target) // if turn is between l and mid, e.g 5,6,7,0,2,4, t = 6
                    r = mid-1;    
                else // no turn between l and r, or turn is between mid and r, because of sorted, nums[r]<nums[mid]
                    l = mid+1; 
            }else{ //target < nums[mid]
                if(nums[mid]>nums[r] & nums[r]>=target)// turn is between mid and r e.g  5,6,7,0,2,  t=0
                    l = mid+1; 
                else  // if turn is between mid and l   e.g 5,6,7,0,1,2,3 t = 1
                    r = mid - 1; 
            }
        }
        return -1;
    }
};


/*
Explanation

Let's say nums looks like this: [12, 13, 14, 15, 16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

Because it's not fully sorted, we can't do normal binary search. But here comes the trick:

If target is let's say 14, then we adjust nums to this, where "inf" means infinity:
[12, 13, 14, 15, 16, 17, 18, 19, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf]

If target is let's say 7, then we adjust nums to this:
[-inf, -inf, -inf, -inf, -inf, -inf, -inf, -inf, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

And then we can simply do ordinary binary search.

Of course we don't actually adjust the whole array but instead adjust only on the fly only the elements we look at. And the adjustment is done by comparing both the target and the actual element against nums[0].

Code

If nums[mid] and target are "on the same side" of nums[0], we just take nums[mid]. Otherwise we use -infinity or +infinity as needed.


*/

class Solution {
public:
int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size()-1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            double num = (nums[mid] < nums[0]) == (target < nums[0]) 
                       ? nums[mid]
                       : target < nums[0] ? -INFINITY : INFINITY; //小于0往右，大于0向左
            /*
            如果nums[mid] > nums[0], target<nums[0]，证明，turn在右边，l = mid+1, 所以设num 为负infinity， 
            比如[4,5,6,7,0,1,2], t = 0, 一开时mid = 3, nums[mid]=7 > nums[0], target = 0 < nums[0]

            如果nums[mid] < nums[0], target>nums[0]，证明，turn在左面边，r = mid-1, 所以设num 为正infinity， 
            比如[5,6,7,0,1,2,3], t = 0, 一开时mid = 3, nums[mid]=0 < nums[0], target = 0 > nums[0]
            
            */
            
            //cout<<" mid "<<mid<<" numid "<<nums[mid]<<" lo "<<lo<<" hi "<<hi<<"  num "<<num<<endl;
            if (num < target)
                lo = mid + 1;
            else if (num > target)
                hi = mid-1;
            else
                return mid;
        }
        return -1;
    }
};


class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto skip_left  = [&]( int x) { return x >= nums[0] ? numeric_limits<int>::min() : x; };
        auto skip_right = [&] (int x) { return x < nums[0] ? numeric_limits<int>::max() : x; };
        auto adjust = [&] (int x) { return target < nums[0] ? skip_left(x) : skip_right(x); };
  
        auto it = lower_bound( nums.begin(), nums.end(), target, [&] (int x, int y) { return adjust(x) < adjust(y); } );
            
        return it != nums.end() && *it == target ? it-nums.begin() : -1;
    }
};