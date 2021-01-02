/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False

*/

class Solution {
public:
    bool isPerfectSquare(int num) {
        long r = num;
        while(r*r>num){
            r = (r+ num/r)/2;
        }
        return r*r == num;
    }
};


class Solution {
public:
    bool isPerfectSquare(int num) {
        long i= 1, j = num/2;
        while(i < j){
            int mid = (i+j)/2;
            if(mid < num/mid) i = mid + 1;
            else j = mid;
        }
        return i*i == num;
    }
};


class Solution {
public:
    bool isPerfectSquare(int num) {
        long  long low = 1, high = num;
        while (low <= high) {
            long  long mid = (low + high) >> 1;
            if (mid * mid == num) {
                return true;
            } else if (mid * mid < num) {
                low = (int) mid + 1;
            } else {
                high = (int) mid - 1;
            }
        }
        return false;
    }
};



/*
Square number is 1 + 3 + 5 + 7 + 9
Math Trick for Square number is 1+3+5+ ... +(2n-1)


For ex :
1 = 1
1+3 = 4
1 + 3 + 5 = 9
1 + 3 + 5 + 7 = 16
.... and so on
 */
class Solution {
public:
    bool isPerfectSquare(int num) {
         int i = 1;
         while (num > 0) {
             num -= i;
             i += 2;
         }
         return num == 0;
    }
};




//Bit Solution
//calculate sqrt(x) by deciding every bit from the most significant to least significant. 
class Solution {
public:
    bool isPerfectSquare(int num) {
         long long i = 0, bit = 1 << 16;
         while(bit){
             i = i | bit;
             if(i * i > num)
                 i ^= bit;
             bit = bit >> 1;
         }
         return i*i == num;
    }
};



class Solution {
public:
    bool isPerfectSquare(int num) {
         long long h = 0;
         while((long long)(1<<h) * (long long)(1<< h) <= num)
             ++h;
         --h;
         long long res = 0;
         int b = h;
        
         while(b>=0){
             if((res |(1<<b)) * (res | (1<<b)) <= num)
                 res |= 1 << b;
             --b;
         }
         return res*res == num;
    }
};