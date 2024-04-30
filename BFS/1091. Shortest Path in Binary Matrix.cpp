class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        static vector<vector<int>> dirs = {{-1,-1}, {-1,0}, {-1,1}, {0, -1}, {0,1}, {1,-1}, {1,0}, {1,1}};
        queue<pair<int,int>>q; q.push({0,0});
        vector<vector<int>> visited(n, vector<int>(n));
        visited[0][0] = 1;
        int distance = 1; 
        while(!q.empty()){
            int size =  q.size();
            for(int a = 0; a < size; ++a){
                auto [i, j] = q.front(); q.pop();
                if (i == n-1 && j == n -1)
                    return distance;
                //cout<<i<<" j "<<j<<endl;
                for(auto & dir: dirs){
                    int x = i + dir[0]; 
                    int y = j + dir[1];
                    if( x < 0 || y < 0 || x >= n || y >= n || visited[x][y] || grid[x][y] == 1) continue;
                    
                    visited[x][y] = 1;
                    q.push({x, y});
                }
            }
            ++distance;
        }
        return -1;
    }
};