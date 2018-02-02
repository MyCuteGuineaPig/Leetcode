/*
64. Minimum Path Sum
https://leetcode.com/problems/minimum-path-sum/description/


Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
[[1,3,1],
 [1,5,1],
 [4,2,1]]
Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the sum.


*/



class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
		if(grid.size() == 0) return 0;
		int n = grid.size(), m = grid[0].size();
        vector<vector<int>>dp(n, vector<int>(m,0));
		dp[0][0] = grid[0][0];
		for(int i = 1; i<n; i++){
			dp[i][0] = dp[i-1][0] + grid[i][0];
		}
		for(int j = 1; j<m; j++){
			dp[0][j] = dp[0][j-1] + grid[0][j];
		}
		
		for(int i = 1; i<n; i++){
			for(int j = 1; j<m; j++){
				dp[i][j] =  dp[i-1][j] < dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
				dp[i][j] += grid[i][j];
			}
		}
		return dp[n-1][m-1];
    }
};

/*

Further inspecting the above code, it can be seen that maintaining pre is for recovering pre[i],
 which is simply cur[i] before its update. So it is enough to use only one vector. 
 Now the space is further optimized and the code also gets shorter.


*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> cur(m, grid[0][0]);
        for (int i = 1; i < m; i++)
            cur[i] = cur[i - 1] + grid[i][0]; 
        for (int j = 1; j < n; j++) {
            cur[0] += grid[0][j]; 
            for (int i = 1; i < m; i++)
                cur[i] = min(cur[i - 1], cur[i]) + grid[i][j];
        }
        return cur[m - 1];
    }
};

