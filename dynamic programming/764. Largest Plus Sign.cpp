/*
764. Largest Plus Sign

In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0. 
What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.

An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, 
down, left, and right, and made of 1s. 
This is demonstrated in the diagrams below. Note that there could be 0s or 1s beyond the arms of the plus sign, 
only the relevant area of the plus sign is checked for 1s.

Examples of Axis-Aligned Plus Signs of Order k:

Order 1:
000
010
000

Order 2:
00000
00100
01110
00100
00000

Order 3:
0000000
0001000
0001000
0111110
0001000
0001000
0000000
Example 1:

Input: N = 5, mines = [[4, 2]]
Output: 2
Explanation:
11111
11111
11111
11111
11011
In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.
Example 2:

Input: N = 2, mines = []
Output: 1
Explanation:
There is no plus sign of order 2, but there is of order 1.
Example 3:

Input: N = 1, mines = [[0, 0]]
Output: 0
Explanation:
There is no plus sign, so return 0.
Note:

N will be an integer in the range [1, 500].
mines will have length at most 5000.
mines[i] will be length 2 and consist of integers in the range [0, N-1].
(Additionally, programs submitted in C, C++, or C# will be judged with a slightly smaller time limit.)


*/


/*
Table like this:  
11111
11111
11111
11111
11011

After We use DP to rule each row 
1 2 3 2 1
1 2 3 2 1
1 2 3 2 1
1 2 3 2 1
1 1 0 1 1

After We use DP to rule each column 
1 1 1 1 1
1 2 2 2 1
1 2 2 2 1
1 2 1 2 1
1 1 0 1 1
最大只能是2
*/


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        unordered_map<int,unordered_set<int>>Banned;
        for_each(mines.begin(),mines.end(),[&](auto mine){Banned[mine[0]].insert(mine[1]);});
        vector<vector<int>>dp(N, vector<int>(N));
        for(int i = 0; i<N; i++){
            int count = 0;
            for(int j = 0; j<N; j++){
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                dp[i][j] = count;
            } 
            
            count = 0;
            for(int j = N-1; j>=0; j--){
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
            }   
        }
        int res = 0;
        for(int j = 0; j<N; j++){
            int count = 0;
            for(int i = 0; i<N; i++){
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
            } 
            
            count = 0;
            for(int i = N-1; i>=0; i--){
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
                res = max(res,dp[i][j]);
            }   
        }
        return res;
        
    }
};


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        if(N == 0) return 0;
        vector<vector<int>>grid(N+1,vector<int>(N+1,N));
        
        for(vector<int>& m : mines)
        {
            grid[m[0]][m[1]] = 0;
        }
        for(int i = 0; i < N; i++)
        {
            int l = 0, r = 0, u = 0, d = 0;
            for(int j = 0, k = N - 1; j < N ; j++, k--)
            {
                //左到右
                grid[i][j] = min(grid[i][j], l = (grid[i][j] == 0 ? 0 : l + 1));
                //右到左
                grid[i][k] = min(grid[i][k], r = (grid[i][k] == 0 ? 0 : r + 1));
                //上到下
                grid[j][i] = min(grid[j][i], u = (grid[j][i] == 0 ? 0 : u + 1));
                //下到上
                grid[k][i] = min(grid[k][i], d = (grid[k][i] == 0 ? 0 : d + 1));
            }
        }
        int ans = 0;
        for(int i = 0; i < N ; i++)
        {
            for(int j = 0; j < N; j++)
            {
                ans = max(ans,grid[i][j]);
            }
        }
        return ans;
    }
};


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>>dp(N, vector<int>(N, N+1));
        for_each(mines.begin(),mines.end(),[&](auto mine){dp[mine[0]][mine[1]] = 0;});
        
        for(int i = 0; i<N; i++){
            int l = 0, r = 0, u = 0, d = 0;
            for(int j = 0, k = N-1; j<N;j++, k--){
                dp[i][j] = min(dp[i][j], l = (dp[i][j]==0 ? 0: l+1));
                dp[j][i] = min(dp[j][i], u = (dp[j][i]==0 ? 0: u+1));
                
                dp[i][k] = min(dp[i][k], r = (dp[i][k]==0 ? 0: r+1));
                dp[k][i] = min(dp[k][i], d = (dp[k][i]==0 ? 0: d+1));
            }
        }
        int res = 0;
        for(int i = 0; i<N; i++) for(int j = 0; j<N;j++)
            res = max(res, dp[i][j]);

        
        return res;
        
    }
};