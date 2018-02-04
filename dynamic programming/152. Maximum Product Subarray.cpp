/*

152. Maximum Product Subarray
https://leetcode.com/problems/maximum-product-subarray/description/

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.


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