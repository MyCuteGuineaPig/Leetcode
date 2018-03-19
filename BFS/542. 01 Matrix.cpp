/*
542. 01 Matrix

Time	Space	Difficulty
O(m * n)	O(m * n)	Medium	

Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.
Example 1: 
Input:

0 0 0
0 1 0
0 0 0
Output:
0 0 0
0 1 0
0 0 0
Example 2: 
Input:

0 0 0
0 1 0
1 1 1
Output:
0 0 0
0 1 0
1 2 1
Note:
The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.

*/



//DP

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>>dp(n,vector<int>(m,0));
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(matrix[i][j]==0)
                    dp[i][j] = 0;
                else dp[i][j] = m+n;
            }
        }

        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(matrix[i][j]!=0 && i>0) {dp[i][j] = min(dp[i][j],dp[i-1][j]+1);}
                if(matrix[i][j]!=0 && j>0) {dp[i][j] = min(dp[i][j],dp[i][j-1]+1);}
            }
        }

        for(int i = n-1; i>=0; i--){
            for(int j = m-1; j>=0; j--){
                if(matrix[i][j]!=0 && i<n-1) {dp[i][j] = min(dp[i][j],dp[i+1][j]+1);}
                if(matrix[i][j]!=0 && j<m-1) {dp[i][j] = min(dp[i][j],dp[i][j+1]+1);}
            }
        }
        return dp;
    }
};



/*

如果有很多1 抱在一起，先检测最外层的1，

*/

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        queue<pair<int,int>>q;
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(matrix[i][j]==0)
                    q.push(make_pair(i,j));
                else matrix[i][j] = m+n;
            }
        }

        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while(q.size()){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(auto d: dirs){
                int newr = r+d[0];
                int newc = c+d[1];
                if (newr >= 0 && newr < n && newc >= 0 && newc < m &&
                matrix[newr][newc]> matrix[r][c] +1){
                    q.push(make_pair(newr, newc));
                    matrix[newr][newc] = matrix[r][c]+1;
                }
                
            }

        }
        return matrix;
    }
};