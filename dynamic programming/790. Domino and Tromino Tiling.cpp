/*
790. Domino and Tromino Tiling
We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.

XX  <- domino

XX  <- "L" tromino
X
Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.

(In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)

Example:
Input: 3
Output: 5
Explanation: 
The five different ways are listed below, different letters indicates different tiles:
XYZ XXZ XYY XXY XYY
XYZ YYZ XZZ XYY XXY
Note:

N  will be in range [1, 1000].


*/


/*
https://leetcode.com/problems/domino-and-tromino-tiling/discuss/116581/Detail-and-explanation-of-O(n)-solution-why-dpn2*dn-1+dpn-3
Detail and explanation of O(n) solution why dp[n]=2*dp[n-1]+dp[n-3]
*/

class Solution {
public:
    const long M = 1e9 + 7;
    int numTilings(int N) {
        long dp[1001] = {0};
        dp[0] = 1;dp[1] = 1;dp[2] = 2;
        for(int i = 3; i<=N; i++)
            dp[i] = ((dp[i-1]*2)%M + dp[i-3])%M;
        return dp[N];
    }
};



/*
Three rule: 
T(N) = T(N-1) + T(N-2) + T_up(N-1) + T_down(N-1)

T_up(N) = T_down(N-1) + T(N-2)

T_down(N) = T_up(N-1) + T(N-2)

which can be written 
T(N) = T(N-1) + T(N-2) + T_down(N-2) + T(N-3) + T_up(N-2) + T(N-3)

which can be regrouped as:

T(N) = T(N-1) + T(N-3) + [T(N-2) + T(N-3) + T_up(N-2) + T_down(N-2)]

Now if you recognize the part in square brakets which is simply T(N-1), we arrive at:

T(N) = 2 * T(N-1) + T(N-3).
*/

class Solution {
public:
    const long M = 1e9 + 7;
    int numTilings(int N) {
        long T_N = 1, T_N_1 = 1, T_N_2 =1, T_UP = 0, T_DOWN = 0, T_UP_1=0, T_DOWN_1 = 0;
        for(int i = 2; i<=N; i++){
            T_N = (T_N_1+T_N_2 +T_UP_1+T_DOWN_1)%M;
            T_UP = (T_DOWN_1+T_N_2)%M;
            T_DOWN = (T_UP_1+T_N_2)%M;
            
            T_N_2 = T_N_1; T_N_1 = T_N;
            T_UP_1 = T_UP; 
            T_DOWN_1 = T_DOWN;
            //cout<<T_N<<endl;
        }
        return T_N;
    }
};