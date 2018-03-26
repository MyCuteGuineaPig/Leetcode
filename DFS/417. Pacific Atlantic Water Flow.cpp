/*

417. Pacific Atlantic Water Flow
Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).


*/

//DFS


class Solution {
public:
    int n, m;
    vector<vector<int>>dir;
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int,int>>res;
        if(matrix.size()==0) return res;
        n = matrix.size(); m = matrix[0].size();
        
        vector<vector<int>>pt(n,vector<int>(m,-1));
        dir = {{-1,0},{0,-1},{1,0},{0,1}};
        for(int i = 0; i<n;i++){
            pt[i][0] = 1;
            dfs(res,pt, matrix, i, 0);
        }
        for(int j = 0; j<m; j++){
            pt[0][j] = 1;
            dfs(res,pt, matrix, 0, j);
        }
        
        for(int i = 0; i<n;i++){
            if(pt[i][m-1]==1)
               res.push_back({i,m-1});
            pt[i][m-1] = 2;
            dfs(res,pt, matrix, i, m-1);
        }
        for(int j = 0; j<m;j++){
            if(pt[n-1][j]==1) 
                res.push_back({n-1,j}); 
            pt[n-1][j] = 2;
            dfs(res,pt, matrix, n-1, j);
        }
        return res;   
    }
    
    /*
    pt = 1 means it from Pacific, 
    pt = 2 means it from Atlantic
    */
    void dfs(vector<pair<int,int>>&res, vector<vector<int>>&pt, vector<vector<int>>& matrix, int i, int j){
        for(int k = 0; k<4; k++){
            int x = i + dir[k][0];  
            int y = j + dir[k][1];
            if(x>=0 && y>=0 && x<n && y < m && matrix[i][j]<=matrix[x][y]){
                if(pt[x][y] == -1){
                    pt[x][y] = pt[i][j];
                    dfs(res,pt,matrix,x,y);
                }   
                else if(pt[i][j] != pt[x][y]){
                    pt[x][y] = pt[i][j];
                    res.push_back({x,y});
                    dfs(res,pt,matrix,x,y);
                }
                   
            }
        }
    }
};


/*
visited[x][y] & preval can be explained into three cases:

visited[x][y] = 1, preval =1 or visited[x][y] = 2, preval = 2 or visited[x][y] = 3, preval = 3, or visited[x][y] = 3, preval = 1, or visited[x][y] = 3, preval = 2
it means (x,y) has been searched before. no need to DFS again. visited[x][y] & preval == preval is true
visited[x][y] = 0, preval =1 or visited[x][y] = 0, preval = 2, or visited[x][y] = 0, preval = 3(push back into vector),
it means (x, y) has not been searched. Do BFS now. visited[x][y] & preval == preval is false
visited[x][y] = 1, preval = 2 or visited[x][y] = 2, preval = 1 or or visited[x][y] = 1, preval = 3, or or visited[x][y] = 2, preval = 3
it means (x, y) is the point we need to push back into vector, visited[x][y] & preval == preval is false. visited[x][y] |= preval; visited[x][y] = 3;

*/

class Solution {
public:
    vector<pair<int, int>> res;
    vector<vector<int>> visited;
    void dfs(vector<vector<int>>& matrix, int x, int y, int pre, int preval){
        if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()  
                || matrix[x][y] < pre || (visited[x][y] & preval) == preval) 
            return;
        visited[x][y] |= preval;
        if (visited[x][y] == 3) res.push_back({x, y});
        dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]); dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
        dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]); dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
    }

    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty()) return res;
        int m = matrix.size(), n = matrix[0].size();
        visited.resize(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dfs(matrix, i, 0, INT_MIN, 1);
            dfs(matrix, i, n - 1, INT_MIN, 2);
        }
        for (int i = 0; i < n; i++) {
            dfs(matrix, 0, i, INT_MIN, 1);
            dfs(matrix, m - 1, i, INT_MIN, 2);
        }
        return res;
    }
};