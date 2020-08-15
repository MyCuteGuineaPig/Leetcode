/*
dp[i][j] denotes the solution of i songs with j different songs. So the final answer should be dp[L][N]

如果没有k的限制
case 1: 最后第j首是new song(choice is N-（j-1))  dp[i][j] += dp[i-1][j-1]*(N-(j-1))
case 2: 如果最后不是新加的, 可以选择j中任何一个作为最后一个  dp[i][j] += dp[i-1][j]*j

如果有k的限制

case 1: 最后第j首是new song(choice is N-（j-1))  dp[i][j] += dp[i-1][j-1]*(N-(j-1))
case 2: 如果最后不是新加的, 
        如果 k >= j: 则为0, 因为要求至少有k个间隔才能replay 
        如果 k < j: 则 i 之前k个数都不能选择（这k个数也不能有重复）  dp[i][j] += dp[i-1][j]*(j-k)

*/


class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        vector<vector<long>>dp(L+1, vector<long>(N+1));
        dp[0][0] = 1;
        int M = pow(10,9)+7;
        
        for(int i = 1; i<=L; ++i){
            for(int j = 1; j<=N && j <= i; ++j){
                
                dp[i][j] = dp[i-1][j-1]*(N-(j-1));
                if(j>K)
                    dp[i][j] +=  dp[i-1][j] * (j-K);
                dp[i][j] = dp[i][j] % M;
            }
        }
        return dp[L][N];
    }
};


//TopDown
class Solution {
public:
    int M = pow(10,9)+7;
    int numMusicPlaylists(int N, int L, int K) {
        vector<vector<long>>dp(L+1, vector<long>(N+1,-1));
        dp[0][0] = 1;
        return topDown(N, N, L, K, dp);
    }
    
    long topDown(int n, int N, int l, int K, vector<vector<long>>&dp){
        if( n > l || n == 0 || l ==0 )
            return n == 0 && l == 0;
        if(dp[l][n]>=0)
            return dp[l][n];
        dp[l][n] = topDown(n-1, N, l-1, K, dp)*(N-n+1);
        if (l > K)
            dp[l][n] += topDown(n, N, l-1, K, dp)*(n-K);
        return dp[l][n] = dp[l][n]%M;
    }
};


//O((L-K)(N-K))
class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        long dp[N + 1][L + 1], mod = 1e9 + 7;
        for (int i = K + 1; i <= N; ++i)
            for (int j = i; j <= L; ++j)
                if ((i == j) || (i == K + 1))  //所有的数不会重复, 所以是factorial(i); 
                /*  比如 i = 6, k = 5,  j = 8 

                        1 2 3 4 5 6 1 2 (最后两首歌顺序只能和第一首，第二首歌顺序一样)
                 */

                    dp[i][j] = factorial(i);
                else
                    dp[i][j] = (dp[i - 1][j - 1] * i + dp[i][j - 1] * (i - K))  % mod;
        return (int) dp[N][L];
    }
    
    long factorial(int n) {
        return n ? factorial(n - 1) * n % (long)(1e9 + 7) : 1;
    }
};


/*
Math Solution: 

https://leetcode.com/problems/number-of-music-playlists/discuss/178960/Java-Fully-detailed-explaination-for-inclusion-exclusion-solution
https://leetcode.com/problems/number-of-music-playlists/discuss/178514/Python3-A-math-solution-O((N-K)-*-log(L-K))

 */