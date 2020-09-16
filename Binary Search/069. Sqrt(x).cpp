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



class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        int start = 1, end = x;
        while (start < end) { 
            int mid = start + (end - start) / 2;
            if (mid <= x / mid && (mid + 1) > x / (mid + 1))// Found the result
                return mid; 
            else if (mid > x / mid)// Keep checking the left part
                end = mid;
            else
                start = mid + 1;// Keep checking the right part
        }
        return start;
    }
};


class Solution {
public:
    int mySqrt(int x) {
        int low = 0,  high = x, mid;
        if(x<2) return x; // to avoid mid = 0
        while(low<high)
        {
            mid = (low + high)/2;
            if(x/mid >= mid) low = mid+1; 
            else high = mid;
        }
        return high-1; //返回low 是错的, 比如8, low = 3, high = 3
    }
};


class Solution {
public:
    int mySqrt(int x) {
        if (0 == x) return 0;
        int left = 1, right = x, ans;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mid <= x / mid) {
                left = mid + 1;
                ans = mid;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
};


class Solution {
public:
    int mySqrt(int x) {
        long lo = 0, hi =  x; //用long, 避免overflow
        
        while (lo <= hi){
            long mid = (lo + hi) / 2;
            
            if (mid * mid > x)
                hi = mid - 1;
            else if(mid * mid < x)
                lo = mid + 1;
            else
                return mid;
        }
        // When there is no perfect square, hi is the the value on the left
        // of where it would have been (rounding down). If we were rounding up, 
        // we would return lo
        return hi;
    }
};


/*
Bit Solution:
O(logn)

Since sqrt(x) is composed of binary bits, 
I calculate sqrt(x) by deciding every bit from the most significant to least significant. 
Since an integer n can have O(log n) bits with each bit decided within constant time, 
this algorithm has time limit O(log n), actually, because an Integer can have at most 32 bits, 
I can also say this algorithm takes O(32)=O(1) time.


 */



class Solution {
public:
    int mySqrt(int x) {
          if(x==0)
            return 0;
        int h=0;
        while((long)(1<<h)*(long)(1<<h)<=x) // firstly, find the most significant bit
            h++;
        h--;
        int b=h-1;
        int res=(1<<h);
        while(b>=0){  // find the remaining bits
            if((long)(res | (1<<b))*(long)(res |(1<<b))<=x)
                res|=(1<<b);
            b--;
        }
        return res;
    }
};