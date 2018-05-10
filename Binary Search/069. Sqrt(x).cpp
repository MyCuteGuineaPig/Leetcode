/*
69. Sqrt(x)
Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.


*/


class Solution {
public:
    int mySqrt(int x) {
        long r = x;
        while(r*r>x){
            r = (r+ x/r)/2;
        }
        return r;
    }
};




/*
    下面的解是rejected， 因为可能r是奇数, x/r也是奇数， r/2 + x/r/2 损失了一位数的精度， 
    比如  25， 12,7,4
        x = 25/2 + 25/25/2  = 12
        x = 12/2 + 25/12/2 = 6 + 1 = 7
        x = 7/2 + 25/7/2 = 3 + 3/2 = 4

    但是假如 r = (r+ x/r)/2;
        x = (7 + 25/7)/2 = (7 + 3)/2 = 不会损失精度

*/
class Solution {
public:
    int mySqrt(int x) {
        long r = x;
        while(r*r>x){
            r = r/2 + x/r/2;
            //cout<<"r "<<r<<endl;
        }
        return r;
    }
};