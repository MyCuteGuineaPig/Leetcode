/*
260. Single Number III

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. 
Find the two elements that appear only once.

Example:

Input:  [1,2,1,3,2,5]
Output: [3,5]
Note:

The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

*/
/*

The two numbers that appear only once must differ at some bit, this is how we can distinguish between them. Otherwise, they will be one of the duplicate numbers.

One important point is that by XORing all the numbers, 
we actually get the XOR of the two target numbers (because XORing two duplicate numbers always results in 0).
Consider the XOR result of the two target numbers; if some bit of the XOR result is 1, 
it means that the two target numbers differ at that location.

需要两次pass
假如需要找的两个数分别为a 和b
第一次pass: 需要区分a 和 b的数
    当xor 弄完所有数, 结果等于res = a ^ b
    因为只出现一次的两个数不一样, 至少一位不同 res !=0, 而res bit = 1的可以区分a 和b
    比如 a = 3（11）,  b =  5（101）,  c = a^b = 10, 第二位的1可以用来区分两个数
第二次pass 只要nums[i] & c, 代表它属于a,  !nums[i] & c代表属于b
其他数不用管，因为不管and c成不成立，都会最终消掉（因为出现两次）

负数的二进制 从111开始减小， 负1最大，
从正数转化方法： positive的数去非，然后加1，比如4  00000100 去非等于 11111011， 加上1等于00000100 (或者是正数-1，取非)
-1  11111111 
-2  11111110
-3  11111101
-4  11111100
-5  11111011

-127 10000001

所以 a & -a, 就是a的最右面第一个位是1的数， 比如  4 & -4 = 4 (100),  5 & -5 = 1  [5= 0101, 取非, 1010, +1 1011]
-a 是正数减1 取非, 正数减1，把数最右侧的1减去，这样，取非就恢复这个1，
*/


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int unique = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        unique &= -unique;
        int a = 0, b = 0;
        for(auto i: nums){
            if(i&unique) a ^= i;
            else b^=i;
        }
        return {a,b};
    }
};


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xor_ = 0;
        for(auto i: nums) xor_ ^= i;
        int first_num = (xor_&(xor_-1))^xor_;
        int a = 0, b = 0;
        for(auto i: nums){
            if(i&first_num) a ^= i;
            else b^=i;
        }
        return {a,b};
    }
};