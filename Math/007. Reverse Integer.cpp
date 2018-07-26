/*
7. Reverse Integer

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

*/


class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while(x){
            int prev = res;
            res = res * 10 + x%10;
            if(res/10 != prev){
                res =0;
                break;
            }
            x /= 10;
        }
        return res;
    }
};


class Solution {
public:
    int reverse(int x) {
        int64_t res = 0;
        int sign = 1;
        
        if (x < 0) {
            x = -x;
            sign = -sign;
        }
        
        while (x) {
            res = res * 10 + x % 10;
            x *= 0.1;
        }
        
        res *= sign;
        
        if (res < INT_MIN || res > INT_MAX) return 0;
        
        return res;
    }
};