class Solution {
public:
    vector<vector<int>>dir = {{-1, 0}, {0, -1}, {1,0}, {0,1}};
    
    void dfs(vector<vector<int>>& grid, int i, int j, vector<vector<int>>&dp, int level){
        if (dp[i][j] >0 && dp[i][j]<=level) return;
        dp[i][j] = level;
        for(auto d: dir){
            int x = i + d[0];
            int y = j + d[1];
            if(x >= 0 &&  y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1){
                dfs(grid, x, y, dp, level + 1);
            } 
        }
        return;
    }

    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>dp(n, vector<int>(m));
        int max_cnt = 0;
        for(int i = 0; i<n; ++i){
            for(int j = 0; j < m; ++j){
                if(grid[i][j] == 2){
                    dfs(grid, i, j, dp, 0);
                }
            }
        }
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<m; ++j){
                if(grid[i][j] == 1)
                {       
                    if( dp[i][j] == 0){         
                        return -1;
                    }
                    max_cnt = max(max_cnt, dp[i][j]);
                }
            }
        }
        return max_cnt;
    }
};