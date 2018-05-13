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
/*
complexity sort O(nlogn), binary search O(nlogmax)
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



/*
priority_queue: sort： O(nlogn) , push, extract O(klogn), total O((N+K)logn)
space:  O(n)
*/


class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        auto cmp = [&](const pair<int,int>&a, const pair<int,int>&b){ return nums[a.second]-nums[a.first] > nums[b.second]-nums[b.first];};
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)>pq(cmp);
        for(int i = 0; i<nums.size()-1;i++)
            pq.push({i,i+1});
        while(--k>0){
            auto it = pq.top(); pq.pop();
            if(++it.second<nums.size()) pq.push(it);
        }
        return nums[pq.top().second]-nums[pq.top().first];
    }
};


