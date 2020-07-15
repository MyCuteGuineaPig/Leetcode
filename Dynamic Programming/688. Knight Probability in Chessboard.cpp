
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        int dir[8][2] = {{-2,-1},{-1,-2},{-2,1},{-1,2},{1,-2},{2,-1}, {2,1}, {1,2}};
        vector<vector<double>>dp(N,vector<double>(N));
        dp[r][c] = 1.0;
        for(int k = 0; k<K; k++){
             vector<vector<double>>newdp(N,vector<double>(N));
            for(int i = 0; i<N; i++){
                for(int j = 0; j<N;j++){
                    if(dp[i][j] != 0){
                        for(auto p: dir){
                            int x = i+p[0], y = j+p[1];
                            if(x<0 || y<0 || x>=N || y >= N) continue;
                            newdp[x][y] += dp[i][j]*1/8;
                        }
                    }
                }
            }
            dp = newdp;
        }
        return std::accumulate(dp.begin(), dp.end(), 0.0, [](auto lhs, const auto& rhs) {
    return std::accumulate(rhs.begin(), rhs.end(), lhs);
});
    }
};


/*

dfs+dp
*/
class Solution {
public:
    vector<vector<vector<long double>>>dp;
    const int dir[8][2] = {{-2,-1},{-1,-2},{-2,1},{-1,2},{1,-2},{2,-1}, {2,1}, {1,2}};
    double knightProbability(int N, int K, int r, int c) {
        dp.resize(N,vector<vector<long double>>(N,vector<long double>(K,-1)));
        return dfs(r,c,N,K-1)/static_cast<long double>(pow(8,K));
    }

    long double dfs(int r, int c, const int& N, int k){
        if(r<0 || c<0 || r>=N || c >= N)
            return 0;
        if(k < 0)
            return 1;
        if(dp[r][c][k]>=0) 
             return dp[r][c][k];
        dp[r][c][k] = 0;
        for(auto p: dir)
            dp[r][c][k] += dfs(r+p[0], c+p[1], N, k-1);
        return dp[r][c][k];
    }
    
};



class Solution {
public:
    vector<vector<int>>move = {{-2,-1}, {-2,1}, {-1,-2},{-1,2}, {1,-2},{1,2},{2,-1},{2,1}};
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<vector<double>>>dp(K+1, vector<vector<double>>(N, vector<double>(N,-1)));
        return topDown(dp, N, K, r,c);
    }
    
    double topDown(vector<vector<vector<double>>>&dp, int N, int K, int i, int j){
        if(i<0 || i>=N || j<0 || j>=N )
            return 0;
        if(K == 0)
            return 1.0;
        if(dp[K][i][j] >= 0)
            return dp[K][i][j];
        
        double res = 0;
        for(auto m: move){
            int x = i + m[0];
            int y = j + m[1];
            res += topDown(dp,N, K-1, x, y) / 8;
        }
        return dp[K][i][j] = res;
    }
};

