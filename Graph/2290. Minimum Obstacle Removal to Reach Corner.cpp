class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        priority_queue<vector<int>, vector<vector<int>>, greater<>>pq;
        vector<vector<int>>cost(n, vector<int>(m, numeric_limits<int>::max()));

        if(grid[0][0] == 1) { 
            pq.push({1, 0, 0});
            cost[0][0] = 1;
        }
        else  { 
            pq.push({0, 0, 0});
            cost[0][0] = 0;
        }
        static vector<vector<int>>dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
        while(!pq.empty()){
            int cur_cost = pq.top()[0], x = pq.top()[1], y = pq.top()[2];
            pq.pop();
            if (x == n-1 && y == m -1){
                return cur_cost;
            }
            for(auto & dir: dirs){
                int i = x + dir[0], j = y + dir[1];
                if( i < 0 || j < 0 || i >= n || j >= m || cost[i][j] <= cur_cost + grid[i][j]) continue;
                cost[i][j] = cur_cost + grid[i][j];
                pq.push({cost[i][j], i, j});
            }
        }
        return -1;
    }
};



class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 1e5 + 1));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        
        pq.push({grid[0][0], 0, 0});
        int dirs[4][2] = {{0, 1},{-1, 0},{1, 0},{0, -1}};
        while (!pq.empty()) {
            auto [c, i, j] = pq.top();
            pq.pop();
            
            if (i == n - 1 && j == m - 1) {
                return c;
            }
            
            for (auto &d: dirs) {
                int x = d[0] + i;
                int y = d[1] + j;
                
                if (x < 0 || y < 0 || x >= n || y >= m)
                    continue;
                
                if (dp[x][y] > grid[x][y] + c) {
                    dp[x][y] = grid[x][y] + c;
                    pq.push({grid[x][y] + c, x, y});
                }
            }
        }
        
        return -1;
    }
};