/*
215. Kth Largest Element in an Array


Find the kth largest element in an unsorted array. 
Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.


*/


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(),nums.end()-k, nums.end());
        return *(nums.end()-k);
    }
};

class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), next(nums.begin(), k - 1), nums.end(), greater<int>());
        return *next(nums.begin(), k - 1);
    }
};


//priority queue
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int>pq;
        for(auto i: nums) pq.push(i);
        while(--k) pq.pop();
        return pq.top();
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int> > q;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (q.size() < k)
                q.push(nums[i]);
            else {
                int min_element = q.top();
                if (min_element <= nums[i]) {
                    q.pop();
                    q.push(nums[i]);
                }
            }
        }
        return q.top();
    }
};


//count sort 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int min_num = *min_element(nums.begin(), nums.end());
        int max_num = *max_element(nums.begin(), nums.end());
        vector<int>cnt(max_num - min_num + 1);
        for(int num: nums){
            ++cnt[num - min_num];
        }
        for(int i = cnt.size()-1; i>=0; --i){
            k -= cnt[i];
            if(k <= 0){
                return i + min_num;
            }
        }
        return -1;
    }
};

/*

Quicksort
In quicksort, in each iteration, we need to select a pivot and then partition the array into roughly two halves:

Elements larger than or equal to the pivot;
Elements smaller than or equal to the pivot.
First let's do an example with the array [3, 2, 1, 5, 4, 6] in the problem statement.
Let's assume in each time we select the leftmost element to be the pivot, 
in this case, 3. We then use it to partition the array, which results in [5, 6, 4, 3, 1, 2]. 
Now 3 is in the 3rd (0-based) position and we know that it is the 4th (1-based) largest element. 
So, have you noticed how partition is related to this problem?

In the above example, now we know that 3 is the 4th largest element. 
If we are asked to find the 2nd largest element, it should be to the left of 3. 
If we are asked to find the 5th largest element, it should be to the right of 3. 
So, in the average sense, the problem is reduced to approximately half of its original size, 
giving the recursion T(n) = T(n/2) + O(n) in which O(n) is the time for partition. 
This recursion, once solved, gives T(n) = O(n) and thus we have a linear time solution. 
Note that since we only need to consider one half of the array, the time complexity is O(n). 
If we need to consider both the two halves of the array, like quicksort, 
then the recursion will be T(n) = 2T(n/2) + O(n) and the complexity will be O(nlogn).

Of course, O(n) is the average/best time complexity. 
In the worst case, the recursion may become T(n) = T(n - 1) + O(n) and the complexity will be O(n^2).

The algorithm is as follows.

Initialize left to be 0 and right to be nums.size() - 1;
Partition the array, if the pivot is at the k-1-th position, return it (we are done);
If the pivot is right to the k-1-th position, update right to be the left neighbor of the pivot;
Else update left to be the right neighbor of the pivot.
Repeat 2.

*/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int p = partition(nums, left, right);
            if (p == k - 1) {
                return nums[p];
            }
            if (p > k - 1) {
                right = p - 1;
            } else {
                left = p + 1;
            }
        }
    }
private:
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) {
                swap(nums[l++], nums[r--]);
            }
            if (nums[l] >= pivot) {
                l++;
            }
            if (nums[r] <= pivot) { 
                r--;
            }
        }
        swap(nums[left], nums[r]);//r是第一个比pivot大的or 等于pivot的，l可能比pivot小了
        return r;
    }
};