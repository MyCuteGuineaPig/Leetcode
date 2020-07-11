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


//Bottom-up DP
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<long long>>dp(m, vector<long long>(n));
        dp[i][j] = 1;
        int mod = pow(10,9)+7;
        vector<vector<int>>move = {{-1,0},{0,-1}, {1,0}, {0,1}};
        long long res = 0 ; 
        for(int z = 0; z<N; ++z){
            vector<vector<long long>>tmp(m, vector<long long>(n));
            for(int ii = 0 ; ii<m; ++ii){
                for(int jj = 0; jj<n; ++jj){
                    if(dp[ii][jj]){
                        for(auto nxt: move){
                            int nxt_i = nxt[0] + ii; 
                            int nxt_j = nxt[1] + jj;
                            if(nxt_i <0 || nxt_j < 0 || nxt_i >= m || nxt_j >= n)
                                res = (res + dp[ii][jj]) % mod;
                            else
                                tmp[nxt_i][nxt_j] = (tmp[nxt_i][nxt_j] + dp[ii][jj])%mod;
                        }
                    }
                }
            }
            
            dp = tmp;

        }
        return res;
    }
};




//DP
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
      uint dp[51][50][50] = {};
      for (auto Ni = 1; Ni <= N; ++Ni)
        for (auto mi = 0; mi < m; ++mi)
          for (auto ni = 0; ni < n; ++ni)
            dp[Ni][mi][ni] = ((mi == 0 ? 1 : dp[Ni - 1][mi - 1][ni]) + (mi == m - 1? 1 : dp[Ni - 1][mi + 1][ni])
                + (ni == 0 ? 1 : dp[Ni - 1][mi][ni - 1]) + (ni == n - 1 ? 1 : dp[Ni - 1][mi][ni + 1])) % 1000000007;
      return dp[N][i][j];
    }
};

//reduce the memory usage by using two grids instead of N
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        unsigned int g[2][50][50] = {};
        while (N-- > 0)
            for (auto k = 0; k < m; ++k)
                for (auto l = 0, nc = (N + 1) % 2, np = N % 2; l < n; ++l)
                    g[nc][k][l] = ((k == 0 ? 1 : g[np][k - 1][l]) + (k == m - 1 ? 1 : g[np][k + 1][l])
                        + (l == 0 ? 1 : g[np][k][l - 1]) + (l == n - 1 ? 1 : g[np][k][l + 1])) % 1000000007;
        return g[1][i][j];
    }
};


//DFS
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<vector<long>>>dp(m, vector<vector<long>>(n, vector<long>(N+1,-1)));
        return dfs(dp, m, n, i, j, N);
    }
    
    int dfs(vector<vector<vector<long>>>&dp, int m, int n, int i, int j, int N ){
        if(N<0)
            return 0;
        if(i < 0 || j<0 || i>=m || j>=n)
            return 1;
        if(dp[i][j][N] >= 0)
            return dp[i][j][N];
        vector<vector<int>>move = {{-1,0},{0,-1}, {1,0}, {0,1}};
        int mod = pow(10,9)+7;
        long long res = 0;
        for(auto nxt: move){
            int nxt_i = nxt[0] + i; 
            int nxt_j = nxt[1] + j;
            res = (res + dfs(dp, m, n, nxt_i, nxt_j, N-1))%mod;
        }        return dp[i][j][N] = res;
    }
};

//BFS
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<int>>move = {{-1,0},{0,-1}, {1,0}, {0,1}};
        int mod = pow(10,9)+7;
        vector<vector<long>>dp(m, vector<long>(n));
        
        queue<vector<int>>q;
        q.push({i,j});
        long res = 0;
        int size = 1;
        dp[i][j] = 1;
        while((size = q.size()) && N--){
            vector<vector<long>>tmp(m, vector<long>(n));
            for(int z = 0; z< size; ++z){
                vector<int>cur = q.front(); q.pop();
                int ii = cur[0], jj = cur[1];
                for(auto nxt: move){
                    int nxt_i = nxt[0] + ii; 
                    int nxt_j = nxt[1] + jj;
                    if(nxt_i <0 || nxt_j < 0 || nxt_i >= m || nxt_j >= n)
                        res = (res + dp[ii][jj]) % mod;
                    else{
                        if(tmp[nxt_i][nxt_j]  == 0)
                            q.push({nxt_i, nxt_j});
                        tmp[nxt_i][nxt_j] = (tmp[nxt_i][nxt_j] + dp[ii][jj])%mod;
                    }
                }
            }
            dp = tmp;
        }
        return res;
    }
};