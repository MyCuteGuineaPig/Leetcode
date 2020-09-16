

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




class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(nums[mid]>nums[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
            int realmid=(mid+rot)%n;
            if(nums[realmid]==target)return realmid;
            if(nums[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    }
};



class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (start <= end){
            int mid = (start + end) / 2;
            if (nums[mid] == target)
                return mid;
        
            if (nums[start] <= nums[mid]){
                 if (target < nums[mid] && target >= nums[start]) 
                    end = mid - 1;
                 else
                    start = mid + 1;
            } 
        
            if (nums[mid] <= nums[end]){
                if (target > nums[mid] && target <= nums[end])
                    start = mid + 1;
                 else
                    end = mid - 1;
            }
        }
        return -1;
    }
};



class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while (l <= r) {
            int mid = (l+r) / 2;
            if (target == nums[mid])
                return mid;
            // there exists rotation; the middle element is in the left part of the array
            if (nums[mid] > nums[r]) {
                if (target < nums[mid] && target >= nums[l])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            // there exists rotation; the middle element is in the right part of the array
            else if (nums[mid] < nums[l]) {
                if (target > nums[mid] && target <= nums[r])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            // there is no rotation; just like normal binary search
            else {
                if (target < nums[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
        }
        return -1;
    }
};



/*

Those three cases look cyclic when should move to left

    nums[0] <= target <= nums[i]
               target <= nums[i] < nums[0]
                         nums[i] < nums[0] <= target

    checks (nums[0] <= target), (target <= nums[i]) and (nums[i] < nums[0]), and I want to know 
    whether exactly two of them are true. They can't all be true or all be false (check it)

 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = int(nums.size()) - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo == hi && nums[lo] == target ? lo : -1;
    }
};