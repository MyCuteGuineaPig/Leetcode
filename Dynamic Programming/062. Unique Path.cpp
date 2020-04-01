/*
62. Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


*/



class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>>dp(m,vector<int>(n,1));
		for(int i = 1; i<m; i++){
			for(int j = 1; j<n; j++)
				dp[i][j] = dp[i-1][j]+dp[i][j-1];
		}
		return dp[m-1][n-1];
    }
};

/*
As can be seen, the above solution runs in O(n^2) time and costs O(m*n) space. 
However, you may have observed that each time when we update path[i][j], 
we only need path[i - 1][j] (at the same column) and path[i][j - 1] (at the left column). 
So it is enough to maintain two columns (the current column and the left column) instead of maintaining the full m*n matrix. 
Now the code can be optimized to have O(min(m, n)) space complexity.

*/
class Solution {
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m); 
        vector<int> pre(m, 1);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++) {
            for (int i = 1; i < m; i++)
                cur[i] = cur[i - 1] + pre[i];
            swap(pre, cur);
        }
        return pre[m - 1];
    }
};


/*

Further inspecting the above code, we find that keeping two columns is used to recover pre[i],
 which is just cur[i] before its update. So there is even no need to use two vectors and one is just enough. 
 Now the space is further saved and the code also gets much shorter.

 */
class Solution {
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++)
            for (int i = 1; i < m; i++)
                cur[i] += cur[i - 1]; 
        return cur[m - 1];
    }
}; 




class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int>dp(n,1);
        for(int i = 1; i<m; i++)
            for(int j = 0 ; j<n; j++)
                dp[j] = dp[j] + (j>0 ? dp[j-1] : 0);
        return dp[n-1];
    }
};

//2020
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>>dp(2, vector<int>(m));
        for(int i = 0; i<n; i++)
            for(int j = 0; j<m; j++)
                dp[i&1][j] = i || j ? dp[(i&1) ^ 1][j] + ( j == 0 ? 0 : dp[i&1] [j-1]) : 1;
	 //i || j false :  dp[0][0] = 1
        return dp[(n-1)&1][m-1];
    }
};
