/*
688. Knight Probability in Chessboard

On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. 
The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, 
then one square in an orthogonal direction.


Each time the knight is to move, it chooses one of eight possible moves uniformly at random 
(even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. 
Return the probability that the knight remains on the board after it has stopped moving.

Example:
Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.


*/
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