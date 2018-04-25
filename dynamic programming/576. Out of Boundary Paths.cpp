/*
576. Out of Boundary Paths

There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. The answer may be very large, return it after mod 109 + 7.

Example 1:
Input:m = 2, n = 2, N = 2, i = 0, j = 0
Output: 6
Explanation:

Example 2:
Input:m = 1, n = 3, N = 3, i = 0, j = 1
Output: 12
Explanation:

Note:
Once you move the ball out of boundary, you cannot move it back.
The length and height of the grid is in range [1,50].
N is in range [0,50].


*/

class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        static const long long M = 1000000007;
        vector<vector<long long>>table(m, vector<long long>(n,0));
        table[i][j] = 1; long long res = 0;
        for(long long k = 0; k<N; k++){
            vector<vector<long long>>newtable(m, vector<long long>(n,0));
            for(long long a = 0; a<m; a++){
                for(long long b = 0; b<n; b++){
                    if(table[a][b]) {
                        if(a-1<0){
                            res = (res+table[a][b])%M;
                        }
                        else{
                            newtable[a-1][b] += table[a][b]%M;
                        }
                        if(a+1>=m){
                            res = (res+table[a][b])%M;
                        }
                        else{
                            newtable[a+1][b] += table[a][b]%M;
                        }
                        
                        if(b-1<0){
                            res = (res+table[a][b])%M;
                        }
                        else{
                            newtable[a][b-1] += table[a][b]%M;
                        }
                        if(b+1>=n){
                            res = (res+table[a][b])%M;
                        }
                        else{
                            newtable[a][b+1] += table[a][b]%M;
                        }
                        table[a][b] = 0;
                    }
                }   
            }
            table = newtable;
        }
        return res%M;
        
    }
};

/*
dfs with memoization, dp[i][j][k] 表示到达i,j后还剩k步，可以最多out of boundary 数量
*/

class Solution {
public:
    long long dp[51][51][51];
    int m, n;
    long long M;
    int findPaths(int m, int n, int N, int i, int j) {
        M = 1000000007;
        memset(dp, -1, sizeof(dp));
        this->m = m; this->n = n;        
        return dfs(i, j, N);
    }

    long long dfs(int i, int j, int k){
        if(i < 0 || j < 0 || i >= m || j>=n){
            return 1;
        }
        else if(k==0)
            return 0;
        if(dp[i][j][k]>=0)
            return dp[i][j][k];
        dp[i][j][k] = ( dfs(i, j+1, k-1)%M+ dfs(i, j-1, k-1)%M + dfs(i+1, j, k-1)%M + dfs(i-1, j, k-1)%M)%M;
        return dp[i][j][k];
    }

};