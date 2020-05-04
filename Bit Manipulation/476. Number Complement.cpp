//100110, its complement is 011001, the sum is 111111

class Solution {
public:
    int findComplement(int num) {
        int i = 0;
        int j = 0;
        
        while (i < num)
        {
            i += 1<<j;
            j++;
        }
        
        return i - num;
    }
};

class Solution {
public:
    int findComplement(int num) {
        int n = 0;
        while (n < num) {
            n = (n << 1) | 1;
        }
        return n - num;
    }
};

// OJ: https://leetcode.com/problems/number-complement/
// Author: github.com/lzl124631x
// Time: O(1) as there are at most 32 bits to move
// Space: O(1)
class Solution {
public:
    int findComplement(int num) {
        unsigned mask = ~0; //~0 = -1
        while (num & mask) mask <<= 1;
        /*
    It's shifting a mask of 1s to the left, producing 0s on the right, 
    for as long as the result of (num & mask) contains a 1, which would equal true.

& in bit shift basically takes the bits of the left and right values, 
overlays them, and keeps the 1s that are in the same place in both values, otherwise 0.    
        
         */
        return ~mask & ~num;
    }
};
For example,


/* 
num          = 00000101
mask         = 11111000
~mask & ~num = 00000010
*/


class Solution {
public:
    int findComplement(int num) {
        int mask = 1;
        while (mask < num) mask = (mask << 1) | 1;
        return ~num & mask;
    }
};

class Solution {
public:
    int findComplement(int num) {
        long mask = 1; //必须是long, 否则 mask <= num (INT_MAX), mask << 1 overflow
        while (mask <= num) mask = (mask << 1);
        return num ^ (mask-1);
    }
};

class Solution {
public:
    int findComplement(int num) {
        int copy = num;
        int i = 0;

        while(copy != 0) {
            copy >>= 1;
            num ^= (1<<i);
            i += 1;
        }
        return num;
    }
};

class Solution {
public:
    //因为最大是32 bit 
    int findComplement(int num) {
        int mask = num;
        mask |= mask >> 1;
        mask |= mask >> 2;
        mask |= mask >> 4;
        mask |= mask >> 8;
        mask |= mask >> 16;
        return num ^ mask;
    }
};