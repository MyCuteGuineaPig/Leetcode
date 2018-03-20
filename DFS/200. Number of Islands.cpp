/*
200. Number of Islands

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3

*/

class Solution {
public:
    int n,m;
    vector<vector<bool>>visited;
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0) return 0;
        n = grid.size();
        m = grid[0].size();
        int num = 0;
        visited.resize(n,vector<bool>(m,false));
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if((!visited[i][j]) && grid[i][j] == '1'){
                    dfs(grid,i, j);
                    num++;
                }
            }
        }
        return num;
    }

    void dfs(vector<vector<char>>& grid, int i, int j){
        visited[i][j] = true;
        vector<vector<int>>dirt = {{-1,0},{0,-1},{1,0},{0,1}};
        for(int k = 0; k<4; k++){
            int x = i+dirt[k][0];
            int y = j+dirt[k][1];
            if(x>=0 && y>=0 && x<n && y<m && grid[x][y] == '1' && !visited[x][y])
                dfs(grid,x,y);
        }

    }
};


//改变grid 的值，让下一次找的时候自动默认此点已经找过了

class Solution {
public:
    int n,m;
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0) return 0;
        n = grid.size();
        m = grid[0].size();
        int num = 0;
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(grid[i][j] == '1'){
                    dfs(grid,i, j);
                    num++;
                }
            }
        }
        return num;
    }

    void dfs(vector<vector<char>>& grid, int i, int j){
        grid[i][j] = '0';
        vector<vector<int>>dirt = {{-1,0},{0,-1},{1,0},{0,1}};
        for(int k = 0; k<4; k++){
            int x = i+dirt[k][0];
            int y = j+dirt[k][1];
            if(x>=0 && y>=0 && x<n && y<m && grid[x][y] == '1')
                dfs(grid,x,y);
        }

    }
};