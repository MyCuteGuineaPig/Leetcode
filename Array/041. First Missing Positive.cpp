/*
41. First Missing Positive

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
Note:

Your algorithm should run in O(n) time and uses constant extra space.

*/

/*
把[1, n]的元素放在i-1的地方，
是O(n)的原因：每个元素最多被调整两次就到了合适的地方，如果A[i] <= 0 or A[i] > nums or A的[A[i] -1]位置 已经等于A[i]，就不用调整了

 比如A = [3,4,-1,1]
 i = 0， swap 1 [-1,4,3,1]  A[0] < -1 continue
 i = 1, swap 1  [-1,1,3,4], 此时4被调整到合适的位置，但是swap之后1还没到，再来一次swap2 [1,-1,3,4],
 i = 2， 不用调整，A[2] == A[A[2] - 1]
 i = 3, 不用调整 A[3] == A[A[3] - 1]

 设pos = A[i] - 1
 可以看出第一步把元素放到pos位置，把原来在pos的位置的元素调整到A[i]
 此时A[pos] 元素已经正确，接来下再也不用调整A[pos] (step = 1)
 而此时从pos 置换过来的数可能位置不对，再重复上一步调整它，需要两步: 1. 先换到A[i], 2.再调整到最终位
 

*/

// 换完后, nums[i] 可能为负数，或者大于 size, 要不然num[i] == i+1
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for(int i = 0; i<nums.size();i++){
            while(nums[i] > 0 && nums[i] <= nums.size() && nums[i]!=nums[nums[i]-1])
                swap(nums[i],nums[nums[i]-1]);
        }
        for(int i = 0; i<nums.size(); i++)
            if(nums[i]!=i+1)
                return i+1;
        return nums.size()+1;
    }
};


//和上个解的区别是: 必须满足 nums[start] == start + 1 才++start, 要不然一直不update start, 
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int start = 0, end = nums.size() - 1;
        while(start <= end){
            int index = nums[start] <= 0 ? -1 : nums[start]-1; // nums[start]可能是  -2147483648， -2147483648 - 1 integer overflow 
            if(index == start) ++start;
            else if(index > start && index <= end && nums[start] != nums[index]) //比如[2,2], 没有 nums[start] != nums[index] 会loop forever
                swap(nums[start], nums[index]);
            else
                swap(nums[start], nums[end--]);
        }
        return start+1;
    }
};

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int start = 0, end = nums.size()-1;
        while(start <= end){
            int index = nums[start] - 1;
            if(index == start) start++;
            else if(index< 0 || index > end || nums[start] == nums[index]) //index 是对比最后一位（被抛弃的前一位），index < 0, 是负数和0， index>end 是大于现在的最后一位的index，
            // nums[start] == nums[index] 是重复index的数
                nums[start] = nums[end--];
            else 
                swap(nums[start], nums[index]);//nums start到了最终位
        }
        return start+1;
    }
};



class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int start = 0, end = nums.size()-1;
        while(start <= end){
            int index = nums[start];
            if(index-1 == start) start++;
            else if(index-1< 0 || index-1 > end || nums[start] == nums[index-1])
                nums[start] = nums[end--];
            else 
                swap(nums[start], nums[index-1]);
        }
        return start+1;
    }
};
