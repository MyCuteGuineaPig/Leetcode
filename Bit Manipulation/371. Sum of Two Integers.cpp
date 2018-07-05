/*
371. Sum of Two Integers

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.


*/

/*

进位： 当两个数相同位都是1，需要加1，向左进一位

variable xorr 用来记录单个1的bit, 不用相加进位的bit，比如1011 + 1001，xor得到0010, 
variable temp = 用来记录两个bit都是1的，相加的话，进位， 比如 1011 + 1001,  a&b = 1001， temp = 10010
这一步相当于1相加，然后进位

a & b 是判断需不需要相加carry，比如 10 和 100， 不需要进位，直接返回 |，  110
如果 是101 和 1, 需要进位， 进行下一步操作

while的作用是可能有连续进位的情况
比如 1011 + 1001,  
第一次xor 和and 后,  a = 1010, b = 10010
这时候a,b的第二位还相同，需要进位， a = 11000, b = 100

*/

class Solution {
public:
    int getSum(int a, int b) {
        while(a & b){
            int xorr = a ^ b;
            int temp = ((a & b)<<1);
            a = xorr;
            b = temp;
        }
        return a | b;
    }
};


class Solution {
public:
    int getSum(int a, int b) {
        return b==0?a:getSum(a^b, (a&b)<<1);
    }
};


/*

"&" AND operation, for example, 2 (0010) & 7 (0111) => 2 (0010)

"^" XOR operation, for example, 2 (0010) ^ 7 (0111) => 5 (0101)

"~" NOT operation, for example, ~2(0010) => -3 (1101) what??? Don't get frustrated here. It's called two's complement.

1111 is -1, in two's complement

1110 is -2, which is ~2 + 1, ~0010 => 1101, 1101 + 1 = 1110 => 2

1101 is -3, which is ~3 + 1

so if you want to get a negative number, you can simply do ~x + 1

Reference:

https://en.wikipedia.org/wiki/Two%27s_complement

https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html

For this, problem, for example, we have a = 1, b = 3,

In bit representation, a = 0001, b = 0011,

First, we can use "and"("&") operation between a and b to find a carry.

carry = a & b, then carry = 0001

Second, we can use "xor" ("^") operation between a and b to find the different bit, and assign it to a,

Then, we shift carry one position left and assign it to b, b = 0010.

Iterate until there is no carry (or b == 0)

*/
class Solution {
public:
    int getSum(int a, int b) {
        while (b) {
            int carry = a & b;
            a ^= b;
            b = carry << 1;
        }
        return a;
    }
};