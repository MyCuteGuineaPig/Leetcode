/*
693. Binary Number with Alternating Bits

Given a positive integer, check whether it has alternating bits: namely, 
if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.

*/


/*
Solution 1: Cancel Bits:

Xor the number with itself shifted right twice and check whether everything after the leading 1-bit became/stayed 0. 
Xor is 0 iff the bits are equal, so we get 0-bits iff the pair of leading 1-bit and the 0-bit in front of it are repeated until the end.


    000101010
  ^ 000001010
  = 000100000

 x ^ (x>>2) 是比较x位和x位移两位是不是把所有bit都cancel了 除了leading的1
 把 n = x ^ (x>>2), 此时应该只有1个1， 然后 n & n -1 = 0 

 如果有相邻两位一样, 1不会重合，那么做xor，不会只有一个leading 的1，  n & n -1 ！= 0, 因为一个数中至少有一个1，
    000100000           000101100
  ^ 000001000         ^ 000001011
  = 000101000         = 000100111

*/
class Solution {
public:
    bool hasAlternatingBits(int n) {
        return !(( n ^= n>>2 ) & n-1);
    }
};





/*Solution 2 - Complete Bits
bool hasAlternatingBits(int n) {
    return !((n ^= n/2) & n+1);
}
Xor the number with itself shifted right once and check whether everything after the leading 1-bit became/stayed 1. Xor is 1 iff the bits differ, so we get 1-bits iff starting with the leading 1-bit, the bits alternate between 1 and 0.

    000101010
  ^ 000010101
  = 000111111

 x ^ (x>>1) 是比较x位和x位移一位，此时每个位上应该都是1, xor得到的数+1 是2^m 
然后 n & n + 1 = 0 

 如果有相邻两位一样, n>>1 和n 不能保证每位上必须有且只有一个，可能1会重合，可能没有1
    000100000           000101100
  ^ 000010000         ^ 000010110
  = 000110000         = 000111010

*/

class Solution {
public:
    bool hasAlternatingBits(int n) {
        return !(( n ^= n>>1 ) & n+1);
    }
};


/*
Solution 3: 
making bits to all one
If (n*3) & (n*3+1) & (n*3+2) == 0, n*3 is either 111..111 or 111..110, then n will be "Binary Number with Alternating Bits".

If n*3 is neither 111..111 nor 111..110, it will has at least one 0 followed by some 1s.

n * 3 = 1....101111111
(n * 3) & (n * 3 + 1) & (n * 3 + 2) = 1..101111 & 1..110000 & 1..10001 = 1..100000 != 0

如果 n 是interleave的bit，比如10101, 1010，把每个bit*3， 相加3次，是11111，或者11110， 只有最后一位可能是0
所以 11111 + 1 or 11110 + 2 是 2^m

*/
class Solution {
public:
    bool hasAlternatingBits(int m) {
        long n = static_cast<long>(m);
        return ! (n*3 & n*3+1 & n*3+2);
    }
};



//比较最近的两个数是不是一样
class Solution {
public:
    bool hasAlternatingBits(int n) {
        while(n){
            if(!(n&1) == !(n&2)) return false;
            n >>= 1;
        }
        return true;
    }
};

//iterative 
class Solution {
public:
    bool hasAlternatingBits(int n) {
        int last = n % 2;
        n >>= 1;
        while(n){
            if(last == n%2) return false;
            last = n%2;
            n >>= 1;
        }
        return true;
    }
};

//也可以写成recursion
class Solution {
public:
    bool hasAlternatingBits(int n) {
        return n < 3 || n % 2 != n/2 % 2 && hasAlternatingBits(n>>1);
    }
};