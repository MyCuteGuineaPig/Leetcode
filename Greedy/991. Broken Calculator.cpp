/*
如果start from x, no clue, should we pick -1 or *2
但是如果start from y, have clue 
 - Y is odd, last operation must be -1, 
 - y is even, have two choice, -1 or * 2
        -  To get last y from y2, two ways:  y2*2， or y2*2 - 1 -1 
            y2*2 - 1 - 1 = (y2-1)*2 and (y2-1)*2 can save one operation
        所以遇到偶数永远 除以2, 最save operations


Intuition:
Considering how to change Y to X
1. Opertation 1: Y = Y / 2 if Y is even
2. Opertation 2: Y = Y + 1


Explanation:
Obviously,
If Y <= X, we won't do Y / 2 anymore.
We will increase Y until it equals to X

So before that, while Y > X, we'll keep reducing Y, until it's smaller than X.
If Y is odd, we can do only Y = Y + 1
If Y is even, if we plus 1 to Y, then Y is odd, we need to plus another 1.
And because (Y + 1 + 1) / 2 = (Y / 2) + 1, 3 operations are more than 2.
We always choose Y / 2 if Y is even.


Why it's right
Actually, what we do is:
If Y is even, Y = Y / 2
If Y is odd, Y = (Y + 1) / 2

We reduce Y with least possible operations, until it's smaller than X.

And we know that, we won't do Y + 1 twice in a row.
Becasue we will always end with an operation Y / 2.

2N times Y + 1 and once Y / 2 needs 2N + 1 operations.
Once Y / 2 first and N times Y + 1 will end up with same result, but needs only N + 1 operations.


Time complexity
We do Y/2 all the way until it's smaller than X,
time complexity is O(log(Y/X)).


 */
class Solution {
public:
    int brokenCalc(int X, int Y) {
        if(Y<=X) return X-Y;
        return 1 + brokenCalc(X, Y & 1 ? Y + 1 : Y/2);
    }
};


class Solution {
public:
    int brokenCalc(int X, int Y) {
        int res = 0;
        while (Y > X) {
            Y = Y % 2 > 0 ? Y + 1 : Y / 2;
            res++;
        }
        return res + X - Y;
    }
};


class Solution {
public:
    int brokenCalc(int X, int Y) {
        int ans = 0;
        for(; Y > X ;  Y = Y % 2 > 0 ? Y + 1 : Y / 2, ans++);
        return (ans + X - Y);
    }
};






/*
1. The only way to increment a X towards Y is to double
2. The fastest way to decrement X towards Y is to decrement by 1 before doubling some number of times.


For example, if given X = 7 and Y = 19,

7 * 2 * 2 = 28 >= 19
至少double 2 次才能超过19, At this point, a possible solution could be to decrement 9 times, 
however it would be faster if we could decrement before doubling.

Consider these two cases:

A. (7 - 1) * 2 * 2 = 24,  save 4 个decrement 
B. (7 * 2 - 1) * 2 = 26, save 2 个 decrement 

This can be seen by comparing the differences. 
The amount we save is equal to 2^(number of doublings that occured since decrementing).


Since we are required to double until X > Y, 
the minimum number of operations results from decrementing as much as possible, as early as possible.


The steps are summarized as follows:

1. Double X until it is greater than Y and take the difference (diff) between X and Y, 
while keeping track of how many times you doubled (mult = 2^(number of doublings until X > Y))

2. Subtract mult from diff until it diff - mult < 0, then divide mult by 2 and repeat this process. 
    This will continue until diff = 0 (We are calculating the minimum number of decrements needed).

3. Return (number of doublings) + (number of times mult is subtracted from diff)


Example: X = 7, Y = 19

1. We need to double 2 times
7 * 2 * 2 > 19 
diff = 28 - 19 = 9
mult = 2 * 2 (2 doublings necessary for X > Y)

2. We need to decrement 3 times (mult is subtracted from diff 3 times)
9 - 4 - 4 - 1 = 0

3. We return 2 + 3 = 5

 */

class Solution {
public:
    int brokenCalc(int X, int Y) {
        if(X > Y){ return X - Y; }
        
        int num_ops = 0;
        int mult = 1;
        while(X < Y){
            X *= 2;
            mult *= 2;
            num_ops++;
        }
        
        int diff = X - Y;
        while(diff != 0){
            if(diff - mult < 0){
                mult /= 2;
            }
            else{
                diff -= mult;
                num_ops++;
            }
        }
        return num_ops;
    }
};