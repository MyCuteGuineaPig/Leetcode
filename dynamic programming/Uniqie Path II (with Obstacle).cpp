
/*
63. Unique Paths II

https://leetcode.com/problems/unique-paths-ii/description/

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		if(obstacleGrid.size() == 0) return 0;
		int n = obstacleGrid.size(), m = obstacleGrid[0].size();
		if(obstacleGrid[n-1][m-1] == 1) return 0;
		vector<vector<int>> path (n, vector<int>(m,0));
		for(int j = 0; j<m; j++){
			if(obstacleGrid[0][j] != 1)
					path[0][j] = 1 ;
            else break;  //初始化第一行，如果有1，  比如 0，0,1,0,0,  初始化第一行， 1， 1， 0， 0， 0 因为第一行第三个就被卡了，过不去了
		}
        
        for(int i = 0; i<n; i++){
			if(obstacleGrid[i][0] != 1)
					path[i][0] = 1 ;
            else break;
		}
		  
		for(int i = 1; i<n; i++){
			for(int j = 1; j<m; j++){
				if(obstacleGrid[i][j] != 1){
					path[i][j] = path[i-1][j]+ path[i][j-1] ;
				}
				
			}
		}
		return path[n-1][m-1];
		
    }
};


/*
Well, this problem is similar to Unique Paths. The introduction of obstacles only changes the boundary conditions and make some points unreachable (simply set to 0).

Denote the number of paths to arrive at point (i, j) to be P[i][j],
 the state equation is P[i][j] = P[i - 1][j] + P[i][j - 1] if obstacleGrid[i][j] != 1 and 0 otherwise.

Now let's finish the boundary conditions. In the Unique Paths problem, we initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j. 
Now, due to obstacles, some boundary points are no longer reachable and need to be initialized to 0. 
For example, if obstacleGrid is like [0, 0, 1, 0, 0], then the last three points are not reachable and need to be initialized to be 0.
 The result is [1, 1, 0, 0, 0].

Now we can write down the following (unoptimized) code. Note that we pad the obstacleGrid by 1 and initialize dp[0][1] = 1 to unify the boundary cases.


*/


class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int> > dp(m + 1, vector<int> (n + 1, 0));
        dp[0][1] = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (!obstacleGrid[i - 1][j - 1])
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[m][n];
    } 
};



/*

Further inspecting the above code, keeping two vectors only serve for the purpose of recovering pre[i], 
which is simply cur[i] before its update. So we can use only one vector and the space is further optimized.


*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<int> cur(m, 0);
        for (int i = 0; i < m; i++) {
            if (!obstacleGrid[i][0])
                cur[i] = 1;
            else break;
        }
        for (int j = 1; j < n; j++) {
            bool flag = false;
            if (obstacleGrid[0][j])
                cur[0] = 0;
            else flag = true;
            for (int i = 1; i < m; i++) {
                if (!obstacleGrid[i][j]) {
                    cur[i] += cur[i - 1]; 
                    if (cur[i]) flag = true;
                }
                else cur[i] = 0; 
            }
            if (!flag) return 0;
        }
        return cur[m - 1];
    }
};











