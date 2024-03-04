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



//BFS 注意*m 不是乘以n

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<int>rotten;
        unordered_set<int>fresh;
        vector<vector<int>>dir = {{-1, 0}, {0, -1}, {1,0}, {0,1}};
        int n = grid.size(), m =grid[0].size();
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<m; ++j){
                if(grid[i][j] == 2) {
                    rotten.push(i*m + j);
                }
                if(grid[i][j] == 1) {
                    fresh.insert(i*m + j);
                }
            }
        }
        int cnt = 0;
        while(!rotten.empty() && !fresh.empty()){//需要fresh 不是empty 
        //如果只是!rotten.empty(), 结果需要cnt - 1
            queue<int>next;
            ++cnt; 
            int size = rotten.size();
            for(int i = 0; i<size; ++i){
                int top = rotten.front();  rotten.pop();
                int r_x = top / m, r_y = top % m;
                for(auto d: dir){
                    int x = r_x + d[0], y = r_y + d[1];
                    if(x >= 0 && y >= 0 && x<n && y < m && fresh.count(x*m + y)){
                        fresh.erase(x*m + y);
                        next.push(x*m + y);
                    }
                }
            }
            rotten.swap(next);
        }
        return fresh.empty() ? cnt: -1;
    }
};


class Solution {
public:
    int rot(vector<vector<int>>& g, int i, int j, int d) {
        if (i < 0 || j < 0 || i >= g.size() || j >= g[i].size() || g[i][j] != 1) return 0;
        g[i][j] = d + 3;
        return 1;
    }
    int orangesRotting(vector<vector<int>>& g, int d = 0, int fresh = 0) {
        for (auto i = 0; i < g.size(); ++i) 
            fresh += count_if(begin(g[i]), end(g[i]), [](int j) { return j == 1; });
        for (auto old_fresh = fresh; fresh > 0; ++d) {
            for (auto i = 0; i < g.size(); ++i)
            for (auto j = 0; j < g[i].size(); ++j)
                if (g[i][j] == d + 2)
                fresh -= rot(g,i+1,j,d) + rot(g,i-1,j,d) + rot(g,i,j+1,d) + rot(g,i,j-1,d);
            if (fresh == exchange(old_fresh, fresh)) return -1;
        }
        return d;
    }
};