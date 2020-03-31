/*
818. Race Car

Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

When you get an instruction "A", your car does the following: position += speed, speed *= 2.

When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)

For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

Now for some target position, say the length of the shortest sequence of instructions to get there.

Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.

Example 2:
Input: 
target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0->1->3->7->7->6.

         0     1  2  3  4  5  6  7  8  9  10  11  12   13  14   15
         0     1  4 |2| 5  7  5 |3| 6  8                9   6  |4|
 speeed        2  1  4    -2 -1  6     
  
       0  1  3   3   3   4
speed  1  2  4  -1   1   2
          A  A  R    R   A

    9从6过来

*/

/*
1 + 2 + 4 + ... + 2 ^ (n-1) = 2 ^ n - 1

Consider two general cases for number i with bit_length n.

1.  i==2^n-1, this case, n is the best way
2. 2^(n-1)-1<i<2^n-1, there are two ways to arrive at i:
   - Use n A to arrive at 2^n-1 first, then use R to change the direction, 
     by here there are n+1 operations (n A and one R),
      then the remaining is same as dp[2^n-1-i]
   -  Use n-1 A to arrive at 2^(n-1)-1 first, then R to change the direction,
      use m A to go backward, then use R to change the direction again to move forward, 
      by here there are n-1+2+m=n+m+1 operations (n-1 A, two R, m A) , 
      current position is 2^(n-1)-1-(2^m-1)=2^(n-1)-2^m, 
      the remaining operations is same as dp[i-(2^(n-1)-1)+(2^m-1)]=dp[i-2^(n-1)+2^m)].


Why dp in this way?

I first think the dp way should be:

dp[i] = min(n+1+dp[2**n-1-i], n-1+2+dp[i-2**(n-1)+1])
But it's wrong, look at the (n-1) A case, we do A for (n-1) times, then do two R, then the situation is the same as dp[i-2**(n-1)+1].
 This can be larger than the actual min operations since, there may be redundant R operations, 
 we can combine RR operation with the remaining (2**(n-1)-1) to i path. 
 So we use m to go backward between the two R operations and count the remaining (2^(n-1)-2^m) to i path to include the combining situation.

For example:

target = 5

The right answer should be AARARAA, positions: 0, 1, 3, 3, 2, 2, 3, 5
But if we use the above formula, the answer is AA (0->3) RR (make speed at 1 again) AARA (3->5)

We can move the last A to the middle of RR, so that we save an operation. That's where the combine can happen.
So we do dp by adding m A between the RR and add the # operations for remaining distance.

If you have better explanation, please let me know. Thanks.



*/

/*
Bottom-up DP:
*/
class Solution {
public:
    int racecar(int target) {
        vector<int>dp(target+1, INT_MAX);
        dp[1] = 1;
        for(int i = 2; i<=target;i++){
            int n = log2(i)+1;
            if((1<<n)-1 == i){
                dp[i] = n;
                continue;
            }
            dp[i] = n + 1 + dp[(1<<n)-1 - i];
            for(int k = 0; k<n; k++)
                dp[i] = min(dp[i], n-1+2+k+dp[i-((1<<(n-1)) - (1<<k))]);
        }
        return dp[target];
    }
};


/*
Top-down DP:
*/

class Solution {
public:
    int dp[10001];
    int racecar(int target) {
        if (dp[target]==0){
            int n = log2(target)+1;
            if((1<<n)-1 == target)
                dp[target] = n;
            else{
                dp[target] = n + 1 + racecar((1 << n)-1 - target);
                for(int k = 0; k<n; k++){
                    dp[target] = min(dp[target], n-1+2+k+racecar(target- ((1 << (n-1)) - (1 << k ) )));
                }
            }
        }
        //cout<<" target "<<target<<" dp "<<dp[target]<<endl;
        return dp[target];
    }
};

class Solution {
public:
    int racecar(int target) {
        vector<int> dp(target + 1);
        for (int i = 1; i <= target; ++i) {
            int k = bitLength(i);
            if (i == (1 << k) - 1) {
                dp[i] = k;
                continue;
            }
            dp[i] = dp[(1 << k) - 1 - i] + k + 1;
            for (int j = 0; j < k; ++j) {
                dp[i] = min(dp[i], dp[i - (1 << (k - 1)) + (1 << j)] + k + j + 1);
            }
        }
        return dp.back();
    }

private:
    uint32_t bitLength(uint32_t n) {
        uint32_t left = 1, right = 32;
        while (left <= right) {
            auto mid = left + (right - left) / 2;
            if ((1 << mid) > n) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

