/*
713. Subarray Product Less Than K

Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Note:

0 < nums.length <= 50000.
0 < nums[i] < 1000.
0 <= k < 10^6.

*/

/*
Sliding Window: 
保持max-product window less than k: 如果当前window乘积大于k, 缩小window 把start向右移动


*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int start = 0, res = 0; 
        int cur = 1;
        for(int i = 0; i<nums.size();i++){
            while(start < i && cur*nums[i]>=k) cur /= nums[start++];
            //cout<<i<<" cur "<<cur<<" start "<<start<<" res "<<res<<endl;
            if(cur*nums[i]<k){
                cur *= nums[i];
                res += i - start + 1;
            }
            else start++; //跳过这个数
        }
        return res;
    }
};


class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int cnt = 1;
        int l = 0;
        int res = 0;
        for(int i = 0; i<nums.size(); ++i){
            cnt *= nums[i];
            while(cnt >= k && l <= i){
                cnt /= nums[l++];
            }
            res += i-l+1;
        }
        return res;
    }
};
