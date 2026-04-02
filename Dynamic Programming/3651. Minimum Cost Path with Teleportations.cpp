class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> points;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j)
                points.push_back({grid[i][j], i, j});
        }
        sort(points.begin(), points.end(), greater<vector<int>>());
        vector<vector<int>>costs (n, vector<int>(m, numeric_limits<int>::max()));
        for(int t = 0; t <=k; ++t) {
            if(t > 0) {
                int mincost = numeric_limits<int>::max();
                for(int cur = 0, r = 0; cur < points.size(); ++cur) {
                    int i = points[cur][1];
                    int j = points[cur][2];
                    mincost = min(mincost, costs[i][j]);
                    if (cur < points.size()-1 && points[cur+1][0] == points[cur][0]) 
                        continue; //same value points jump 因为一样value 谁cost大谁小都有可能

                    for(; r <=cur ; r++){
                        i = points[r][1];
                        j = points[r][2];
                        costs[i][j] = mincost;
                    }
                }
            }
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < m; ++j) {
                    if(i == 0 && j == 0) costs[i][j] = 0;
                    if (i!= 0)
                        costs[i][j] = min(costs[i][j], costs[i-1][j] + grid[i][j]);
                    if (j!= 0)
                        costs[i][j] = min(costs[i][j], costs[i][j-1] + grid[i][j]);
                }
            }
        }
        return costs[n-1][m-1];
    }
};