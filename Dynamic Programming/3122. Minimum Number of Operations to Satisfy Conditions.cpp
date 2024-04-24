class Solution {
public:
    int dfs(unordered_map<int,unordered_map<int,int>>& dp, vector<vector<int>>&counter, int j, int prev_color , int m){
        if(j == m) {
            return 0;
        }
        if (dp.count(j) && dp[j].count(prev_color)){
            return dp[j][prev_color];
        }
        dp[j][prev_color] = 0;
        for(int c = 0; c <= 9; ++c){
            if(c != prev_color)
                dp[j][prev_color]  = max(dp[j][prev_color], counter[j][c] + dfs(dp, counter, j+1, c, m));
        }
        return dp[j][prev_color];
    }


    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid[0].size(), n = grid.size();
        unordered_map<int, unordered_map<int,int>>dp;
        vector<vector<int>>counter(m, vector<int>(10));
        for(int j = 0; j < m ; ++j){
            for(int i = 0; i < n; ++i){
                ++counter[j][grid[i][j]];
            }
        }
        return n*m - dfs(dp,counter,  0, -1, m);
    }
};


class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid[0].size(), n = grid.size();
        vector<int>dp(10);
        for(int j = 0; j < m ; ++j){
            vector<int>counter(10);
            for(int i = 0; i < n; ++i){
                ++counter[grid[i][j]];
            }

            vector<int>tmp(10, 1e9+7);
            for(int c = 0; c < 10; ++c){
                int cnt = numeric_limits<int>::max();
                for(int prev = 0; prev< 10; ++prev){
                    if (c == prev) continue;
                    cnt = min(cnt, dp[prev] + n - counter[c]);
                }
                tmp[c] = min(cnt, (int)1e9 + 7);
            }
            dp = tmp;
        }
        return *min_element(dp.begin(), dp.end());
    }
};