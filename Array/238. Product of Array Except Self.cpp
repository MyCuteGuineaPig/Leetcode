/*
238. Product of Array Except Self

Given an array nums of n integers where n > 1,  
return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Example:

Input:  [1,2,3,4]
Output: [24,12,8,6]
Note: Please solve it without division and in O(n).

Follow up:
Could you solve it with constant space complexity? 
(The output array does not count as extra space for the purpose of space complexity analysis.)

*/


/*

res[i] 表示 nums[0: i-1]的乘积，
right 记录从结尾到nums[i+1: end]的乘积
最后res[i] = res[i] * right


Given numbers [2, 3, 4, 5], regarding the third number 4, 
the product of array except 4 is 2*3*5 which consists of two parts: 
left 2*3 and right 5. The product is left*right. We can get lefts and rights:

Numbers:     2    3    4     5
Lefts:            2  2*3 2*3*4
Rights:  3*4*5  4*5    5      
Let’s fill the empty with 1:

Numbers:     2    3    4     5
Lefts:       1    2  2*3 2*3*4
Rights:  3*4*5  4*5    5     1
We can calculate lefts and rights in 2 loops. The time complexity is O(n).



*/


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int>res(nums.size(),1);
        for(int i = 1; i < nums.size(); i++)
            res[i] = res[i-1]* nums[i-1];
        int right = 1;
        for(int i = nums.size()-1; i>=0; i--){
            res[i] = res[i]*right;
            right *= nums[i];
        }
        return res;
    }
};


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) {
            return {};
        }

        vector<int> left_product(nums.size());

        left_product[0] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            left_product[i] = left_product[i - 1] * nums[i - 1];
        }

        int right_product = 1;
        for (int i = static_cast<int>(nums.size()) - 2; i >= 0; --i) {
            right_product *= nums[i + 1];
            left_product[i] = left_product[i] * right_product;
        }

        return left_product;
    }
};

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int left=1, right=1;
        vector<int> result(n, 1);
        for(int i=0; i<n; i++){
            result[i]*=left; //乘以所有i左面的
            result[n-1-i]*=right; //乘以所有的i的右面的
            left*=nums[i];
            right*=nums[n-1-i];
        }
        return result;
    }
};

/*
EXPLAINATION:

Thinking of the 'nums' array [1, 2, 3, 4, 5, 6], 
and the 'result' array [1, 1, 1, 1, 1, 1]. 
Every number in 'nums' will be multiplied in 'result' array except itself, then we will get the map below:

  1 2 3 4 5 6
  -----------
1|  1 1 1 1 1
2|2   2 2 2 2
3|3 3   3 3 3
4|4 4 4   4 4
5|5 5 5 5   5
6|6 6 6 6 6

(horizontal axis is nums array, vertical axis is multiplied times)
Noticed the regular pattern of the upper triangular and lower triangular. 
Using integers to store the products of the lower and upper triangulars, then we can do it in one pass:

i : left index of the nums array
j : right index of the nums array
left : left products multiplied from nums[0] to nums[i].
right : right products multiplied from nums[j] to nums[nums.length - 1].
We multiply left to result[i + 1] ((i, i + 1) in the uppper triangular),

and multiply right to result[j - 1] ((j, j - 1) in the lower triangular),

finally we have calculated the products of the nums except current.

*/