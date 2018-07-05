/*
342. Power of Four

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example:
Given num = 16, return true. Given num = 5, return false.

Follow up: Could you solve it without loops/recursion?


*/

/*
4^n = (3+1)^n  = 3^n +.... + 1^n 所以power of 4 - 1 可以整除3
所以判断power of 4, 除了判断是不是power of 2 (n&n-1), 
还要判断4^n-1 是不是可以整除3，

*/
class Solution {
public:
    bool isPowerOfFour(int n) {
        return n>0 && (n&(n-1)) == 0 && (n-1 )% 3 == 0;
    }
};

class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && (num & (num - 1)) == 0 &&
               ((num & 0b01010101010101010101010101010101) == num);
    }
};

class Solution {
public:
    bool isPowerOfFour(int num) {
        while(num>0){
            if(num==1) return true;
            if((num&3)!=0) return false;
            num=num>>2;
        }
        return false;
    }
};