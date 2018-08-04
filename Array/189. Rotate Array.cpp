/*

189. Rotate Array

Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
Note:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?

*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
};


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (!nums.empty()) {
            k %= nums.size();
            reverse(nums.begin(), nums.begin() + nums.size() - k);
            reverse(nums.begin() + nums.size() - k, nums.end());
            reverse(nums.begin(), nums.end());
        }
    }
};

//# Swap the last k elements with the first k elements.
class Solution 
{
public:
    void rotate(int nums[], int n, int k) 
    {
        for (; k = k%n; n -= k, nums += k)
        {
            // Swap the last k elements with the first k elements. 
            // The last k elements will be in the correct positions
            // but we need to rotate the remaining (n - k) elements 
            // to the right by k steps.
            for (int i = 0; i < k; i++)
            {
                swap(nums[i], nums[n - k + i]);
            }
        }
    }
};

/*
But since Java doesn't have all those nice trick of swap() and pointer operations, 
I modified it to store the processed section at the end, and then handle the rest at the beginning of the array.

The idea is: for a given K, I can put (n - k) elements to their final locations at the end of the array in a single pass; 
after that, the problem is reduced to a sub-problem of processing the remaining elements.

For example, [1,2,3,4,5,6,7] k = 3, in the first iteration in the while loop, 
put n-k=4 elements to the final places at the end. Will have to start from the last element, 
so that the other elements will be bubbled down correctly. It will look like this after the first iteration: [7, 5, 6, 1, 2, 3, 4]

The 2nd iteration will handle the remaining 3 elements: [7, 5, 6]; to determine the new k, 
we first observe that the # of out-of-order elements being put to the beginning of the array are (range % k), 
and in this example, only one element (7) is out of order. then to move the out-of-order elements back in order, 
we just need to rotate the remaining 3 elements to the right by k' = n - (range % k) = 2.

therefore, after 2nd iteration in while loop, we will get [6, 5, 7], then n <- 2, k <- 1;

the 3rd iteration starts with sub array [6,5], k =1, and we will get [5,6] after it, and then n <- 1.
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.size() == 0) return;
        int n = nums.size();
        while ((k %= n) > 0 && n > 1) {
            int range = n - k;
            for (int i = 1; i <= range; i++) {
                int val = nums[n - i];
                nums[n - i] = nums[n - i - k];
                nums[n - i - k] = val;
            }
            n = k;
            k = n - (range % k);
        }
    }
};
