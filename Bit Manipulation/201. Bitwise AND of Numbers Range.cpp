/*

201. Bitwise AND of Numbers Range


Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: [5,7]
Output: 4
Example 2:

Input: [0,1]
Output: 0
*/


/*
The hardest part of this problem is to find the regular pattern.
For example, for number 26 to 30
Their binary form are:
11010
11011
11100　　
11101　　
11110

Because we are trying to find bitwise AND, so if any bit there are at least one 0 and one 1, it always 0.
 In this case, it is 11000.
So we are go to cut all these bit that they are different. In this case we cut the right 3 bit.

一位一位比较digit，直到小和大的数一样，每移动一次，大和小都向右前进一位
直到移动k次大的和小的一样，那么此时的digit是重合的结果，再把移动后的m向左前进k位就是最后的结果
比如 101, 100, 移动两次, m = n =1
再比如11, 1011, 11到1011肯定经过100, 1000, 所以结果是0

*/

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int i = 0;
        while(m != n){
            m >>= 1;
            n >>= 1;
            i++;
        }
        return m<<i;
    }
};


class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
       return (n>m)?rangeBitwiseAnd(m>>1,n>>1)<<1:m;
    }
};