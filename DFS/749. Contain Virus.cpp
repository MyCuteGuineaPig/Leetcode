/*

749. Contain Virus

A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

The world is modeled as a 2-D array of cells, where 0 represents uninfected cells, and 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region -- the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night. There will never be a tie.

Can you save the day? If so, what is the number of walls required? If not, and the world becomes fully infected, return the number of walls used.

Example 1:
Input: grid = 
[[0,1,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,0]]
Output: 10
Explanation:
There are 2 contaminated regions.
On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:

[[0,1,0,0,0,0,1,1],
 [0,1,0,0,0,0,1,1],
 [0,0,0,0,0,0,1,1],
 [0,0,0,0,0,0,0,1]]

On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
Example 2:
Input: grid = 
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output: 4
Explanation: Even though there is only one cell saved, there are 4 walls built.
Notice that walls are only built on the shared boundary of two different cells.
Example 3:
Input: grid = 
[[1,1,1,0,0,0,0,0,0],
 [1,0,1,0,1,1,1,1,1],
 [1,1,1,0,0,0,0,0,0]]
Output: 13
Explanation: The region on the left only builds two new walls.
Note:
The number of rows and columns of grid will each be in the range [1, 50].
Each grid[i][j] will be either 0 or 1.
Throughout the described process, there is always a contiguous viral region that will infect strictly more uncontaminated squares in the next round.


*/




class Solution {
public:
    int containVirus(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty())
            return 0; 
        int thisStepMaxWall = -1, res = 0;
        while(thisStepMaxWall != 0){
            thisStepMaxWall = buildWall(grid);
            res += thisStepMaxWall;
        }
        return res;
    }

    int buildWall (vector<vector<int>>& grid){
        vector<unordered_set<int>> new_infected;  //int:  x*m + y which is next step infected,
        vector<unordered_set<int>> virus;  
        // unordered_set<pair<int,int>> is group of next step new infection
        vector<vector<int>>visited(grid.size(), vector<int>(grid[0].size()));
        int wall = 0, maxinfectedArea = 0;
        int maxIndex = -1;
        for(int i = 0; i<grid.size(); ++i){
            for(int j = 0; j<grid[0].size(); ++j){
                if(!visited[i][j] && grid[i][j] == 1){
                    new_infected.push_back({});
                    virus.push_back({});
                    int newwall = dfs(grid, new_infected.back(), virus.back(), visited, i, j);
                    if(new_infected.back().size() > maxinfectedArea){
                        wall = newwall;
                        maxinfectedArea = new_infected.back().size();
                        maxIndex = new_infected.size() -1 ;
                    }
            
                }
            }
        }
        
        if (maxIndex >= 0){ //new_infected size == 1 last one 
            const int m = grid[0].size();
            for(int i = 0; i<new_infected.size(); ++i){
                if (i == maxIndex){
                    for(auto next: virus[i])
                        grid[next/m][next%m] = -1; //equal -1 下一步就不会算 
                }
                else{
                    for(auto next: new_infected[i])
                        grid[next/m][next%m] = 1; //被感染的 
                }
            }
        }
        return wall;  
    }

    int dfs(const vector<vector<int>>& grid, unordered_set<int>& new_infected, unordered_set<int>& virus, vector<vector<int>>& visited, int x, int y){
        vector<int>dir = {-1,0,1,0};
        int res = 0; 
        const int m = grid[0].size();
        visited[x][y] = 1;
        virus.insert(x*m + y);
        for(int z = 0; z < 4; ++z){
            int i = x + dir[z], j = y + dir[(z+1)%4];
            if (i<0 || j < 0 || i >= grid.size() || j>=grid[0].size() || visited[i][j] || grid[i][j] == -1)
                continue;
            if(grid[i][j] == 1)
                res += dfs(grid, new_infected, virus, visited, i, j);
            else{ 
                new_infected.insert(i*m + j);
                res ++ ;
            }
        }
        return res; 
    }

};
