/*
167. Two Sum II - Input array is sorted

Given an array of integers that is already sorted in ascending order, 
find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target,
 where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.


*/


/*
two pointer, 一个从开始位置，一个从末尾的位置, sum>target, right--, 小于target， left++
如果两个pointer都是从头开始，加入sum<target, 既可以left++, 也可以right++。所以无法判断
*/


class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size()-1;
        while(true){
            if(numbers[i]+numbers[j] == target) return {i+1,j+1};
            if(numbers[i]+numbers[j]<target) i++;
            else j--;
        }
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        
        while (left != right) {
            const auto sum = numbers[left] + numbers[right];
            if (sum > target) {
                --right;
            } else if (sum < target) {
                ++left;
            } else {
                return {left + 1, right + 1};
            }
        }

        return {0, 0};
    }
};