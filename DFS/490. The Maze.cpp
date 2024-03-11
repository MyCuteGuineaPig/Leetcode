class Solution {
public:
    bool dfs(vector<vector<int>>& maze, vector<int>& destination, int i, int j, vector<vector<int>>& visited){
        visited[i][j] = 1;
        int n = maze.size(), m = maze[0].size();
        if (i == destination[0] && j==destination[1])
            return true;
        for(auto& dir: dirs){
            int x = i , y = j;
            while(isValid(x+ dir[0], y+ dir[1], n , m, maze)){
                x += dir[0];
                y += dir[1]; 
            } //走到不能走了
            if (isValid(x, y, n , m, maze) && visited[x][y] == 0)
                if (dfs(maze,destination, x, y, visited ))
                    return true;
        }
        return false;
    }

    bool isValid(int i, int j, int n, int m, vector<vector<int>>& maze){
        return i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0;
    }

    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0,-1}, {0,1}};
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int cnt = 0; 
        int n = maze.size(), m = maze[0].size();
        vector<vector<int>> visited(n, vector<int>(m));
        return dfs(maze, destination, start[0], start[1], visited);
    }
};

/*

[[0,0,1,0,0],
 [0,0,0,0,0],
 [0,0,0,1,0],
 [1,1,0,1,1],
 [0,0,0,0,0]]

start  = [0,4]
destination = [1,2] 
result = True 


*/



class Solution {
public:
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0,-1}, {0,1}};

    bool isValid(int i, int j, int n, int m, vector<vector<int>>& maze){
        return i >= 0 && i < n && j >= 0 && j < m && maze[i][j] == 0;
    }

    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int cnt = 0; 
        int n = maze.size(), m = maze[0].size();
        vector<vector<int>> visited(n, vector<int>(m));
        queue<pair<int,int>> q;  q.push({start[0], start[1]}); 
        visited[start[0]][start[1]] = 1;
        while(!q.empty()){ 
            int size = q.size();
            for(int a = 0; a < size; ++a){
                auto [i, j] = q.front(); q.pop();
                if (i == destination[0] && j == destination[1]){
                    return true;
                }
                for(auto& dir: dirs){
                    int x = i , y = j;
                    while(isValid(x+ dir[0], y+ dir[1], n , m, maze)){
                        x += dir[0];
                        y += dir[1]; 
                    } 
                    
                    if (isValid(x, y, n , m, maze) && visited[x][y]== 0){
                        
                        visited[x][y] = 1;
                        q.push({x, y});
                    } 
                }
            }
        }   
        return false;
    }
};