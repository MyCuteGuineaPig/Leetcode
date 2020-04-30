/*

152. Maximum Product Subarray
https://leetcode.com/problems/maximum-product-subarray/description/

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.


*/


/*
这道题妙就妙在它不仅仅依赖了一个状态（前一个数所能获得的最大乘积），而是两个状态（最大和最小乘积）。

比较简单的dp问题可能就只是会建立一个dp[]，然后把最大值放到其中。
但是这道题给我们打开了新的思路：我们的dp数组里面可以存更多的信息。
而上面的解法之所以没有用dp数组的原因是dp[i]只依赖于dp[i - 1]因此没有必要把前面所有的信息都存起来，

只需要存前一个dp[i-1]的最大和最小的乘积就可以了。下面的代码使用了自定义的内部类Tuple,
从而可以同时存imax和imin,并将所有的imax和imin存到了dp数组中。虽然稍显复杂，但是有助于加深理解。
 */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.size()==0) return 0;
        int curmax = nums[0], curmin = nums[0], result = nums[0];
        for(int i = 1; i<nums.size();i++){
            if(nums[i]<0)
                swap(curmax, curmin);
            curmax = max(nums[i], curmax*nums[i]);
            curmin = min(nums[i], curmin*nums[i]);
            result = max(result,curmax);
        }
        return result;
    }
};


/*


           2,   6,  (swap)  -2,  3,   1,   4,   3    (Swap)  -2
    max    2    12   2      -2   3    3   12    36   -2     
    min    2    2    12     -2   -2   -2  -2   -2    36

           -2,   3,  (swap)  -4
    max    -2    3   -6     -24
    min    -2   -6    3     
*/


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        
        int curmin = 0, curmax = 0, res = 0, tmpmax;
        for(int i = 0; i < n; ++i)
        {
            tmpmax = curmax;
            curmax = max(nums[i], max(tmpmax*nums[i], curmin*nums[i]));
            curmin = min(nums[i], min(tmpmax*nums[i], curmin*nums[i]));
            res = max(curmax, res);

        }
        return res;
    }
};


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int localmax = nums[0], localmin=nums[0], globalmax = nums[0];
        for(int i = 1; i<nums.size();i++){
            int temp = max(nums[i],nums[i]*localmax,nums[i]*localmin);
            localmin = min(nums[i],nums[i]*localmax,nums[i]*localmin);
            localmax = temp;
            globalmax = std::max(localmax,globalmax);
            
        }
        return globalmax;
    }
    
    int max(int a, int b, int c){
        return std::max(a,std::max(b,c));
    }
    int min(int a, int b, int c){
        return std::min(a,std::min(b,c));
    }
};


/**
Calculate prefix product in A.
Calculate suffix product in A.
Return the max.

First, if there's no zero in the array, 
then the subarray with maximum product must start with the first element or end with the last element. 
And therefore, the maximum product must be some prefix product or suffix product. 
So in this solution, we compute the prefix product A and suffix product B, and simply return the maximum of A and B.

Why? Here's the proof:

Say, we have a subarray A[i : j](i != 0, j != n) and the product of elements inside is P. 
Take P > 0 for example: if A[i] > 0 or A[j] > 0, then obviously, we should extend this subarray to include A[i] or A[j]; 
if both A[i] and A[j] are negative, then extending this subarray to include both A[i] and A[j] to get a larger product. 
Repeating this procedure and eventually we will reach the beginning or the end of A.

What if there are zeroes in the array? 
Well, we can split the array into several smaller ones. 
That's to say, when the prefix product is 0, we start over and compute prefix profuct from the current element instead. 
And this is exactly what A[i] *= (A[i - 1]) or 1 does.

 */

/**
 Explanation 2:

The key point of this problem is: there are only two patterns.
One is "aBcD", and the other is "aBcDe", where I use lowercase to denote a negative number, 
and use upper case to denote a positive number.

For the first pattern, the maximum product would be "aBcD"; 

and for the second pattern, the maximum product would be "max (aBcD, BcDe)". 
 */

/** 最好的解释
 Explantion 3

 Detailed Explanation:
First, Consider there is no zero, and if we get the products of all the numbers:

1) We will have a negative result if there are odd numbers of negative -> max 
    ((product of (0, last negative)), (product of (first negative, last num))
2) We will have a positive result if there are even numbers of negative -> 
    product of all the numbers

Above all, we can get the max by going through the array from both start and end, then we won't miss any situations

If there is a zero, that means we would have two subproblems(unless the zero is at index 0 or last index), 

if two zeros, 3 subs, all the way up. 
We still can calculate from the very beginning and end at the same time, then we would get the result.

 */

class Solution {
public:
    int maxProduct(vector<int> A) {
        int n = A.size(), res = A[0], l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            l =  (l ? l : 1) * A[i];
            r =  (r ? r : 1) * A[n - 1 - i];
            res = max(res, max(l, r));
        }
        return res;
    }
};