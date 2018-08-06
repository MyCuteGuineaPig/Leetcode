/*
581. Shortest Unsorted Continuous Subarray


Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, 
then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

*/


/*

寻找从左面起，小于左侧最大的数的右侧边界 为 right
寻找从右侧起，大于右侧最小的数为左侧边界，为 left

比如           0    1    2    3    4      5     6
             [2,   6,   4,   8,   10,    9,   15]
maxleft       2    6    6    8    10    10 
left          0    0    2    2    2      5         
minright           4    4    9    9      9    15        
right              1    4    4    4     -1     -1


*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int max_left = nums[0], min_right = nums.back();
        int left = 0, right = -1;
        for(int i = 1; i<nums.size(); i++){
            max_left = max(max_left, nums[i]);
            min_right = min(min_right, nums[nums.size()-1-i]);
            if(nums[i] < max_left) 
                right = i;
            if(nums[nums.size()-1-i] > min_right)
                left = nums.size()-1-i;
        }
        return right - left + 1;
    }
};



class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n= nums.size();
        int mn = nums[n-1], mx = nums[0];
        int start = -1, end = -2;
        
        for (int i = 1; i<nums.size(); i++) {
            mx = max(mx, nums[i]);
            mn = min(mn, nums[n-1-i]);
            if (nums[i] != mx) end = i;
            if (nums[n-1-i] != mn) start = n-1-i;
        }
        
        return end - start +1;
    }
};


/*

Solution 

two pointer, 当有数小于current max, 往回开始找起点start, start只能减小, end只能增加, res = end - start + 1

*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int max_ = nums[0], start = -1, end = -2;
         for(int i = 1; i<nums.size(); i++){
            if(nums[i] < max_){
                if(start == -1) start = i-1;
                while(start-1>=0 && nums[start-1]>nums[i]) start--;
                end = i;
            }
            max_ = max(nums[i], max_);
        }
        return end - start + 1;
    }
};

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int start = -1, end = -1,  max = INT_MIN;
        for(int i=0; i<nums.size();i++){
            if(max>nums[i]){
                if(start == -1)start = i-1;
                while(start-1>=0 && nums[start-1]>nums[i])start--;
                end = i+1;
            }
            else max = nums[i];
        }
        return end - start;   
    }
};


/*

Solution 3 Sort, 先sort 再对比sort 之后结果一不一样
*/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> sorted(nums);
        sort(sorted.begin(), sorted.end());
        int n = nums.size(), i = 0, j = n - 1;
        while (i < n && nums[i] == sorted[i]) {
            i++;
        }
        while (j > i && nums[j] == sorted[j]) {
            j--;
        }
        return j + 1 - i;
    }
};


/*

Solution 4 

先找点break 左面持续增加的点，  如果没有找到，代表已经sort 了， return 0
再找break 从右侧起持续减小的点， 

从[l, r] 找最大值和最小值

从左侧l起，向左去掉去比min 还大的，比如 [2,5,7,3], l, r区间是[7,3], 最小值是3，往左侧找比3小的起点(区间包含比min大的）)
从右侧r起，向右去掉比max还小的点， 比如 [1,10,9,7,8,13], l, r区间是[10,9], 最大值是10， 往右找比10大的点（区间包含比max小的）

*/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        int n = nums.size();
        if (n <= 1) return 0;

        int left = 0, right = n - 1;
        while (left < n - 1 && nums[left] <= nums[left + 1]) ++left;
        if (left == n - 1) return 0; // return 0 if already sorted.
        // Or we know the array is unsorted
        // So, it's no need to judge right > 0
        while (/*right > 0 && */nums[right] >= nums[right - 1]) --right;

        //for [1,3,2,2,2] ,left = 1, right = 2
        
        int rmin = INT_MAX, lmax = INT_MIN;  
        for (int i = left; i <= right; ++i) {
            if (nums[i] > lmax) lmax = nums[i];
            if (nums[i] < rmin) rmin = nums[i];
        }
        while (left >= 0 && nums[left] > rmin) --left;
        while (right < n && nums[right] < lmax) ++right;
        return right - left - 1;
    }
};