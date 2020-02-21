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

//DFS
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



class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(),0));
        int count = 0;
        helper(grid, visited, count, 0, 0);
        return count;
    }
    
    void helper(vector<vector<char>>& grid, vector<vector<int>> &visited, int & count, int x, int y){
        if(x>=grid.size()) return;
        
        if(!visited[x][y] && grid[x][y] == '1'){
            count += 1;
            DFS(grid, visited, x, y);
        }
        if(y == grid[0].size() -1  ) helper(grid, visited, count, x+1, 0);
        else helper(grid, visited, count, x, y+1);
    }

    void DFS(vector<vector<char>>& grid, vector<vector<int>> &visited, int x, int y){
        if(x<0 || y<0 || x>=grid.size() || y >= grid[0].size() || visited[x][y]) {  return; }
        visited[x][y] = 1;
        if(grid[x][y]=='0') return;
        DFS(grid, visited, x-1, y);
        DFS(grid, visited, x+1, y);
        DFS(grid, visited, x, y+1);
        DFS(grid, visited, x, y-1);
    }
};


//BFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0, offsets[] = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    grid[i][j] = '0';
                    queue<pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k], c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                todo.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};

//Union Find with Rank Heuristics

class Solution {
public:

    class DisjointSet{
        vector<int>parents;
        int cnt = 0; 
        vector<int>ranks;
        private: 
            int find(int a){
                return parents[a] == a ? a : parents[a] = find(parents[a]);
            }
        
        public:
            int get_size() const {return cnt;}
            DisjointSet(int size){
                parents.resize(size);
                ranks.resize(size);
            }
            void assign(int x){
                parents[x] = x;
                ++cnt;
            }
            void join(int a, int b){
                int px = find(a), py = find(b);
                if(px == py) 
                    return;
                --cnt;
                if(ranks[px] > ranks[py]){
                    parents[py] = px;
                }else if(ranks[px] < ranks[py])
                    parents[px] = py;
                else{
                    ++ranks[px];
                    parents[py] = px;
                }
                
            }
    };

    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty())
            return 0;
        int n = grid.size(), m = grid[0].size();
        DisjointSet uf(m*n);
        for(int i =0; i<n; i++)
            for(int j = 0; j<m; ++j)
                if(grid[i][j] == '1')
                    uf.assign(i*m + j);

        for(int i = 0; i<n; i++)
            for(int j = 0; j<m; ++j){
                if(i> 0 && grid[i][j] == '1' && grid[i-1][j] == '1')
                    uf.join(i*m + j, (i-1)*m + j);
                if(j> 0 && grid[i][j] == '1' && grid[i][j-1] == '1')
                    uf.join(i*m + j, i*m + j-1);
            }
        return uf.get_size();
    }

    
};


//Union Find
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        vector<int>id(m*n, -1);
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == '1'){
                    count ++;
                    id[i*n+j] = i*n + j;
                }
            }
        }
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == '1'){
                    if(i>0 && grid[i-1][j] == '1' ) unionFind(i*n + j, (i-1)*n+j, id, count); //top 
                    if(j>0 && grid[i][j-1] == '1' ) unionFind(i*n + j, i*n + j -1, id, count ); //left
                }
            }
        }
        
        return count;
    }

    int find(int x, vector<int>& id){
        if(id[x] == x) return x;
        id[x] = find(id[x],id);
        return id[x]; 
    }
    
    void unionFind (int x, int y, vector<int>&id, int & count){
        int px = find(x,id);
        int py = find(y,id);
        if(px!=py){
            id[px] = id[py];
            count--;
        }
    }
    
};
