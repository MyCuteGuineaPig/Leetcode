/**
 * Complexity: 
 * O(m*n)
 */

class Solution {
public:
    vector<pair<int, int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    unordered_map<int, int> turns[7]{{}, 
        {{0, 0}, {1, 1}}, {{2, 2}, {3, 3}}, {{0, 2}, {3, 1}},   //0 is right, 1 left, 2 is down, 3 is up
        {{3, 0}, {1, 2}}, {{0, 3}, {2, 1}}, {{2, 0}, {1, 3}}};
    bool trace(vector<vector<int>> &g, int dir) {
        int i = 0, j = 0, m = g.size(), n = g[0].size();
        while(min(i, j) >= 0 && i < m && j < n) {
            auto road = g[i][j];
            if (turns[road].count(dir) == 0)
                return false;
            if (i == m - 1 && j == n - 1)
                return true;
            dir = turns[road][dir];
            i += dirs[dir].first, j += dirs[dir].second;
            if (i == 0 && j == 0)
                return false;
        }
        return false;        
    }
    bool hasValidPath(vector<vector<int>>& g) {
        return trace(g, 0) || trace(g, 1) || trace(g, 2) || trace(g, 3);
    }

};


/**
 * 图: 把每个图分成9小份，然后dfs, 最后只要到最后一份的中心位置 if (i == g.size() - 2 && j == g[i].size() - 2)  即可
 * https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/discuss/547225/C%2B%2B-with-picture%3A-track-direction-%2B-upscaled-grid
 */

class Solution {
public:
    bool dfs(vector<vector<bool>> &g, int i, int j) {
        if (min(i, j) < 0 || i >= g.size() || j >= g[i].size() || !g[i][j])
            return false;
        if (i == g.size() - 2 && j == g[i].size() - 2) 
            return true;
        g[i][j] = false;
        return dfs(g, i - 1, j) || dfs(g, i + 1, j) || dfs(g, i, j + 1) || dfs(g, i, j - 1);
    }
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> g(m * 3, vector<bool>(n * 3));
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j) {
                auto r = grid[i][j];
                g[i * 3 + 1][j * 3 + 1] = true;
                g[i * 3 + 1][j * 3 + 0] = r == 1 || r == 3 || r == 5;
                g[i * 3 + 1][j * 3 + 2] = r == 1 || r == 4 || r == 6;
                g[i * 3 + 0][j * 3 + 1] = r == 2 || r == 5 || r == 6;
                g[i * 3 + 2][j * 3 + 1] = r == 2 || r == 3 || r == 4;
            }
        return dfs(g, 1, 1);    
    }
};