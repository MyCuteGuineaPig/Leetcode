class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        unordered_set<string>st;
        for(int i = 0; i<grid.size(); ++i){
            for(int j = 0; j<grid[0].size(); ++j)
                if(grid[i][j] == 1){
                    string cur;
                    helper(grid, i, j, cur, '0');
                    st.insert(cur);
                }
                    
        }
        return st.size();
    }
    
    void helper(vector<vector<int>>& grid, int i, int j, string& cur, char direction){
        if(i<0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] != 1)
            return;
        
        cur.push_back(direction);
        grid[i][j] = -1;
        helper(grid, i-1, j, cur, 'L');
        helper(grid, i, j-1, cur,'D');
        helper(grid, i+1, j, cur,'R');
        helper(grid, i, j+1, cur, 'U');
        cur.push_back('0');
    }
};


/*
BFS
*/
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, offsets[] = {0, 1, 0, -1, 0};
        unordered_set<string> islands;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    grid[i][j] = 0;
                    string island;
                    queue<pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k], c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c]) {
                                grid[r][c] = 0;
                                todo.push({r, c});
                                island += to_string(r - i) + to_string(c - j);
                            }
                        }
                    }
                    islands.insert(island);
                }
            }
        }
        return islands.size();
    }
};



class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<vector<vector<int>>> islands; //不能用unordered_set 因为vector 不能hash
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<vector<int>> island;
                if (dfs(i, j, i, j, grid, m, n, island))
                    islands.insert(island);
            }
        }
        return islands.size();
    }

private:
    int delta[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0};

    bool dfs(int i0, int j0, int i, int j, vector<vector<int>>& grid, int m, int n, vector<vector<int>>& island) {
        if (i < 0 || m <= i || j < 0 || n <= j || grid[i][j] <= 0) return false;
        island.push_back({i - i0, j - j0});
        grid[i][j] *= -1;
        for (int d = 0; d < 4; d++) {
            dfs(i0, j0, i + delta[d][0], j + delta[d][1], grid, m, n, island);
        }
        return true;
    }
};