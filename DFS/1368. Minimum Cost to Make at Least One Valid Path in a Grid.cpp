class Solution {
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), cost = 0;
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        dfs(grid, 0, 0, dp, cost, q);
        while (!q.empty()) {
            cost++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                pair<int, int> p = q.front();
                int r = p.first, c = p.second;
                q.pop();
                for (int j = 0; j < 4; j++)
                    dfs(grid, r + dir[j][0], c + dir[j][1], dp, cost, q);
            }
        }
        return dp[m - 1][n - 1];
    }
    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& dp, int cost, queue<pair<int, int>>& q) {
        int m = grid.size(), n = grid[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n || dp[r][c] != INT_MAX)return;
        dp[r][c] = cost;
        q.push(make_pair(r, c));
        int nextDir = grid[r][c] - 1;
        dfs(grid, r + dir[nextDir][0], c + dir[nextDir][1], dp, cost, q);
    }

};


class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        deque<pair<int, int>> q{{0, 0}};  // for the pair, the first element is the cell position, the second is the path cost to this cell
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        unordered_set<int> visited;
        
        int res = 0;
        while(!q.empty())
        {
            auto t = q.front(); 
            q.pop_front();

            int curi = t.first / n, curj = t.first % n;
            if (visited.insert(t.first).second)  // If we have never visited this node, then we have the shortest path to this node
                res = t.second;
            
            if (curi == m-1 && curj == n-1)
                return res;
            
            for (auto dir: dirs)
            {
                int x = curi + dir[0];
                int y = curj + dir[1];
                int pos = x * n + y;
                if (x<0 || x>=m || y<0 || y>=n || visited.count(pos)) continue;
                
                int cost;
                if (grid[curi][curj] == 1 && dir[0] == 0 && dir[1] == 1) cost = 0;
                else if (grid[curi][curj] == 2 && dir[0] == 0 && dir[1] == -1) cost = 0;
                else if (grid[curi][curj] == 3 && dir[0] == 1 && dir[1] == 0) cost = 0;
                else if (grid[curi][curj] == 4 && dir[0] == -1 && dir[1] == 0) cost = 0;
                else cost = 1;
                
                if (cost == 1)
                    q.push_back({pos, t.second + cost});
                else
                    q.push_front({pos, t.second + cost});
            }
        }
        return res;
    }
};


//Dijkstra
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int m = grid.size(), n = grid[0].size();
        using ti = tuple<int, int, int>;
        priority_queue<ti, vector<ti>, greater<>> pq;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        pq.emplace(0, 0, 0);
        while (pq.size()) {
            auto [cost, x, y] = pq.top(); pq.pop();
            if (vis[x][y]) continue;
            vis[x][y] = 1;
            if (x == m - 1 && y == n - 1) return cost;
            for (int i = 0; i < 4; ++i) {
                auto &[dx, dy] = dir[i];
                int nx = dx + x, ny = dy + y;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !vis[nx][ny]) {
                    if (i == grid[x][y] - 1) {
                        pq.emplace(cost, nx, ny);
                    } else {
                        pq.emplace(cost + 1, nx, ny);
                    }
                }
            }
        }
        return -1;
    }
};

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        const int m(grid.size()), n(grid[0].size());
        vector<vector<int>> dp(m, vector<int>(n, 10000));
        dp[0][0] = 0;
        
        while (true) {
            vector<vector<int>> temp(dp);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    dp[i][j] = min(dp[i][j], min(i ? dp[i - 1][j] + (grid[i - 1][j] == 3 ? 0 : 1) : 10000, 
                                                 j ? dp[i][j - 1] + (grid[i][j - 1] == 1 ? 0 : 1) : 10000));
            // It depends on the complexity of pattern to break the loop
			if (temp == dp) break;
            for (int i = m - 1; i >= 0; --i)
                for (int j = n - 1; j >= 0; --j)
                    dp[i][j] = min(dp[i][j], min(i != m - 1 ? dp[i + 1][j] + (grid[i + 1][j] == 4 ? 0 : 1) : 10000,
                                                 j != n - 1 ? dp[i][j + 1] + (grid[i][j + 1] == 2 ? 0 : 1) : 10000));
        }
        
        return dp[m - 1][n - 1];
    }
};