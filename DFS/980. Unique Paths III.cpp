class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int zero = 0, start_i = 0, start_j = 0;
        int m =  grid.size(), n = grid[0].size();
        for(int i = 0; i<m; ++i){
            for(int j = 0; j<n; ++j){
                if(grid[i][j] == 0) ++zero;
                if(grid[i][j] == 1) {start_i = i; start_j = j;}
            }
        }
        
        
        vector<vector<int>>visited(m,vector<int>(n,0));
        return helper(grid, visited, start_i, start_j, zero+1);
    }
    
    vector<vector<int>>dir = {{-1,0},{0,-1},{1,0},{0,1}};
    int helper(vector<vector<int>>& grid, vector<vector<int>>&visited, int i, int j, int zero){
        if(grid[i][j] == 2 && zero == 0)
            return 1;
        visited[i][j] = 1;
        int res = 0;
        for(auto nxt: dir)
        {
            int x = i + nxt[0], y = j + nxt[1];
            if(x <0 || y < 0 || x>= grid.size() || y>=grid[0].size() || grid[x][y] == -1 || grid[x][y] == 1 || visited[x][y])
                continue;
            res += helper(grid, visited, x, y, zero-1);
        }
        visited[i][j] = 0;
        return res;
    }
    
};

/*

Runtime: O(3 ^ n), where n is the total number of cells without obstacles.
Memory: O(n) for the DFS stack.
 */
class Solution {
public:
    int dfs(vector<vector<int>>& g, int i, int j, int s, int t_s) {
      if (i < 0 || j < 0 || i >= g.size() || j >= g[0].size() || g[i][j] == -1) return 0;
      if (g[i][j] == 2) return s == t_s ? 1 : 0;
      g[i][j] = -1;
      int paths = dfs(g, i + 1, j, s + 1, t_s) + dfs(g, i - 1, j, s + 1, t_s) +
        dfs(g, i, j + 1, s + 1, t_s) + dfs(g, i, j - 1, s + 1, t_s);
      g[i][j] = 0;
      return paths;
    }
    int uniquePathsIII(vector<vector<int>>& g) {
      auto i1 = 0, j1 = 0, t_steps = 0;
      for (auto i = 0; i < g.size(); ++i)
        for (auto j = 0; j < g[0].size(); ++j) {
          if (g[i][j] == 1) i1 = i, j1 = j;
          if (g[i][j] != -1) ++t_steps;
        }
      return dfs(g, i1, j1, 1, t_steps);
    }
};





class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int zeros = 1;
        int x_start, y_start, x_end, y_end;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++) {
                if(grid[i][j] == 0) zeros++;
                else if(grid[i][j] == 1) {
                    x_start = i;
                    y_start = j;
                }
                else if(grid[i][j] == 2) {
                    x_end = i;
                    y_end = j;
                }
            }
        }
        
        return paths(grid, x_start, y_start, x_end, y_end, 0, zeros);
    }
    
    int paths(vector<vector<int>> &grid, 
              int x, int y, int x_end, int y_end, int covered, int required) {
        if(x == x_end && y == y_end && covered == required) {
            return 1;
        }
                
        grid[x][y] = -1;
        int res = 0;
        vector<vector<int>> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        for(auto &dir : dirs) {
            int new_x = x + dir[0];
            int new_y = y + dir[1];
            if(valid_index(new_x, new_y, grid.size(), grid[x].size())
              && (grid[new_x][new_y] == 0 || grid[new_x][new_y] == 2)) {
                res += paths(grid, new_x, new_y, x_end, y_end, covered + 1, required);
            }
        }
        grid[x][y] = 0;
        
        return res;
    }
    
    int valid_index(int i, int j, int n, int m) {
        return i >= 0 && j >= 0 && i < n && j < m;
    }
};





/* 
 Time:  O(m * n * 2^(m * n))
 Space: O(m * n * 2^(m * n))
https://github.com/kamyu104/LeetCode-Solutions/blob/master/C++/unique-paths-iii.cpp
解释见： https://leetcode.com/problems/unique-paths-iii/discuss/221965/Java-DFS-with-Memo
*/
class Solution {
private:
    template <typename T>
    struct PairHash {
        size_t operator()(const pair<T, T>& p) const {
            size_t seed = 0;
            seed ^= std::hash<T>{}(p.first)  + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= std::hash<T>{}(p.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };
    using Lookup = unordered_map<pair<int, int>, int, PairHash<int>>;

public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int todo = 0;
        pair<int, int> src, dst;
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                if (grid[r][c] % 2 == 0) {
                    todo |= index(grid, r, c);
                }
                if (grid[r][c] == 1) {
                    src = make_pair(r, c);
                } else if (grid[r][c] == 2) {
                    dst = make_pair(r, c);
                }
            }
        }
        Lookup lookup;
        return dp(grid, src, dst, todo, &lookup);
    }
    
private:
    int dp(const vector<vector<int>>& grid,
           const pair<int, int>& src,
           const pair<int, int>& dst,
           int todo,
           Lookup *lookup) {
        if (src == dst) {
            return (todo == 0);
        }
        const auto& key = make_pair(index(grid, src.first, src.second), todo);
        if (lookup->count(key)) {
            return (*lookup)[key];
        }

        static const vector<pair<int, int>> directions = 
            {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int result = 0;
        for (const auto& d : directions) {
            int r = src.first + d.first, c = src.second + d.second;
            if (0 <= r && r < grid.size() &&
                0 <= c && c < grid[0].size() &&
                grid[r][c] % 2 == 0 && 
                todo & index(grid, r, c)) {

                result += dp(grid, make_pair(r, c), dst,
                             todo ^ index(grid, r, c), lookup);
            }
        }

        (*lookup)[key] = result;
        return (*lookup)[key];
    }
    
    int index(const vector<vector<int>>& grid, int r, int c) {
        return 1 << (r * grid[0].size() + c);
    }
};