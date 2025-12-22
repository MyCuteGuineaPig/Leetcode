/*
695. Max Area of Island

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.



*/


class Solution {
public:
    int n, m;
    vector<vector<bool>> visited;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.size()==0) return 0;
        int result = 0;
        n = grid.size(); m = grid[0].size();
        visited.resize(n,vector<bool>(m,false));
        for(int i = 0; i<n ; i++)
            for(int j = 0; j<m; j++)
                if(!visited[i][j] && grid[i][j] == 1)
                    result = max(result, dfs(grid,i,j));
        return result;        
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j){
        if(i<0 || j<0  || i>= n || j>=m || grid[i][j]!= 1 || visited[i][j]) return 0;
        visited[i][j] = true;
        int cumsum = 1;
        cumsum += dfs(grid,i-1, j);
        cumsum += dfs(grid,i, j-1);
        cumsum += dfs(grid,i+1, j);
        cumsum += dfs(grid,i, j+1);
        return cumsum;
    }
    
};


class Solution {
public:
    int n, m;
    vector<vector<bool>> visited;
    vector<vector<int>>dir;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.size()==0) return 0;
        int result = 0;
        n = grid.size(); m = grid[0].size();
        dir = {{-1,0},{0,-1},{1,0},{0,1}};
        visited.resize(n,vector<bool>(m,false));
        for(int i = 0; i<n ; i++)
            for(int j = 0; j<m; j++)
                if(!visited[i][j] && grid[i][j] == 1)
                    result = max(result, bfs(grid,i,j));
        return result;        
    }
    
    int bfs(vector<vector<int>>& grid, int i, int j){
        visited[i][j] = true;
        int cumsum = 0;
        queue<pair<int,int>>q;
        q.push({i,j});
        while(q.size()){
            cumsum++;
            i = q.front().first;
            j = q.front().second;
            q.pop();
            for(int k = 0; k<4; k++){
                int x = i+dir[k][0];
                int y = j+dir[k][1];
                if(x<0 || y<0  || x>= n || y>=m || grid[x][y]!= 1 || visited[x][y]) continue;
                visited[x][y] = true;
                q.push({x,y});
            }
            
        }
        return cumsum;
    }
    
};



class Solution {
public:
    int n, m;
    vector<vector<bool>> visited;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if(grid.size()==0) return 0;
        int result = 0;
        n = grid.size(); m = grid[0].size();
        visited.resize(n,vector<bool>(m,false));
        for(int i = 0; i<n ; i++)
            for(int j = 0; j<m; j++)
                if(!visited[i][j] && grid[i][j] == 1)
                    result = max(result, dfs(grid,i,j));
        return result;        
    }
    
    int dfs(vector<vector<int>>& grid, int i, int j){
        if(i<0 || j<0  || i>= n || j>=m || grid[i][j]!= 1 || visited[i][j]) return 0;
        visited[i][j] = true;
        return dfs(grid,i-1, j) + dfs(grid,i, j-1) + dfs(grid,i+1, j) + dfs(grid,i, j+1) + 1;
    }
    
};



class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m));
        vector<int>dirs = {0, -1, 0, 1, 0};
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            visited[i][j] = 1;
            int cnt = 1; 
            for(int a = 0; a < 4; ++a){
                int x = i + dirs[a];
                int y = j + dirs[a+1];
                if ( x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == 0 || visited[x][y])
                    continue;
                cnt += dfs(x, y);
            }
            return cnt;
        };
        int res = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j) {
                if (grid[i][j] && !visited[i][j])
                    res = max(res, dfs(i,j));
            }
        }
        return res;
    }
};