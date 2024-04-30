class Solution {
public:
    vector<vector<int>>dirs = {{-1, 0}, {0,-1}, {0,1}, {1,0}};
        
    int getArea(vector<vector<int>>& grid, int i, int j, int area_index){
        grid[i][j] = area_index;
        int res = 1;
        for(auto & dir: dirs){
            int x = i + dir[0];
            int y = j + dir[1];
            if (x < 0 || y < 0 ||  x>= grid.size() || y>=grid[0].size() || grid[x][y] != 1) continue;
            res += getArea(grid, x, y, area_index);
        }
        return res;
    } 

    int largestIsland(vector<vector<int>>& grid) {
        unordered_map<int,int>area;
        int area_index = 2;
        int n = grid.size(), m = grid[0].size();
        int res = 0;  //get maxarea. could be all 1 in the grid
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if (grid[i][j] ==  1){
                    area[area_index] = getArea(grid,  i,  j,  area_index);
                    res =  max(res, area[area_index]);
                    area_index += 1;
                    
                }
            }
        }

        for(int i = 0; i <n; ++i ){
            for(int j = 0; j < m; ++j){
                if(grid[i][j] == 0){
                    int cur = 1;
                    unordered_set<int>area_index_set;//shouldn't proceed the same index twice
                    //the same index means belong to the same island
                    for(auto & dir: dirs){
                        int x = i + dir[0];
                        int y = j + dir[1];
                        if (x < 0 || y < 0 ||  x>= grid.size() || y>=grid[0].size() || grid[x][y] < 2 || area_index_set.count( grid[x][y])) continue;
                        
                        int area_index = grid[x][y];
                        area_index_set.insert(area_index);
                    
                        cur += area[area_index];
                    }
                    res = max(res, cur);
                }
            }
        }
        return res;
    }
};