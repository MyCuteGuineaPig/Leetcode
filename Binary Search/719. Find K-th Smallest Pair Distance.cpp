/*
719. Find K-th Smallest Pair Distance

Given an integer array, return the k-th smallest distance among all the pairs. 
The distance of a pair (A, B) is defined as the absolute difference between A and B.

Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0 
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.
Note:
2 <= len(nums) <= 10000.
0 <= nums[i] < 1000000.
1 <= k <= len(nums) * (len(nums) - 1) / 2.


*/

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int l = 0, r = nums.back()-nums[0]; //l = 0 因为可能有重复的比如[1,1,3]
        while(l<r){
            int mid = (l+r)>>1;
            //cout<<mid<<" l "<<l<<" r "<<r<<endl;
            if(isEnough(nums,k,mid)) r = mid;
            else l = mid+1;
        }
        return l;
    }

    bool isEnough(const vector<int>& nums,int k,int target){
        int cnt = 0,j = 1;
        for(int i = 0; i<nums.size()-1; i++){
            while(j<nums.size()&& nums[j]-nums[i]<=target)j++;
            cnt += j-i-1;
            if(cnt>=k) return true;
        }
        return false;
    }
};






class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        //PLAN 1
        //traverse nums O(n^2) compute all dists
        //find kth smallest O(k)
        
        //PLAN 2
        //function pairNum(int k) : given a dist "d", return how many pairs dist smaller than "d" O(NlogN)
        //binary search "d" from 0 to 1000000 log(1000000)
        //store nums in map, search a+k, pos
        
        //how to implement pairNum(int k)
        //find the first d == k
        std::sort(nums.begin(), nums.end());
        int left = 0, right = nums.back() - nums.front();
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int d = piarNum(nums, mid);
            if(d >= k) {
                right = mid - 1;
            } else if (d < k) {
                left = mid + 1;
            }
        }
        return left;
    }
private:
    //two point
    int piarNum(const vector<int>& nums, int d) {
        //nums[j] - nums[i] < d
        //nums[i+1]
        int j = 0;
        int l = nums.size();
        int ret = 0;
        for(int i = 0; i < l; ++i) {
            //i,j the first valid pair
            while(j < l && nums[j] - nums[i] <= d) j++;
            ret += j - 1 - i;
        }
        return ret;
    }
};


class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int low = 0, high = nums.back()-nums.front();
        while (low<high) {
            int count = 0, j = 0, mid = (low+high)/2;
            for (int i=1; i<nums.size(); i++) {
                while (j<i&&nums[i]-nums[j]>mid) j++;
                count+=(i-j);
            }
            if (count>=k) high = mid;
            else low = mid+1;
        }
        return low;
    }
};