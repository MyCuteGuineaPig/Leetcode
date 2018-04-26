/*
741. Cherry Pickup

In a N x N grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through;
1 means the cell contains a cherry, that you can pick up and pass through;
-1 means the cell contains a thorn that blocks your way.
Your task is to collect maximum number of cherries possible by following the rules below:

Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
Example 1:
Input: grid =
[[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
Output: 5
Explanation: 
The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
Note:

grid is an N by N 2D array, with 1 <= N <= 50.
Each grid[i][j] is an integer in the set {-1, 0, 1}.
It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.

*/



class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N, -1));
        dp[0][0] = grid[0][0];
        for (int k = 1, maxK = 2*N-2; k <= maxK; ++k) {
            for (int i = min(N-1, k); i >= 0; --i) {
                if (k - i >= N) {
                    //cout<<" exception "<<" i "<<i<<" k "<<k<<endl;
                    continue;
                }
                for (int j = min(N-1, k); j >= 0; --j) {
                    //cout<<" i "<<i<<" "<<" j "<<j<<" k "<<k;
                    if (k - j >= N || grid[i][k - i] < 0 || grid[j][k - j] < 0) {
                        dp[i][j] = -1;
                        //cout<<" out "<<endl;
                        continue;
                    }
                    int cherris = dp[i][j];//person1 向右走，person2 向右走
                    //cout<<" cherris "<<cherris;
                    if (i > 0)  cherris = max(cherris, dp[i-1][j]);//[i-1][j] person1 向下走，person2 向右走
                    if (j > 0)  cherris = max(cherris, dp[i][j-1]);//[i][j-1] person1 向右走，person2 向下走
                    if (i > 0 && j > 0)  cherris = max(cherris, dp[i-1][j-1]);//person1 向下走，person2 向下走
                    //cout<<" after compare "<<cherris;
                    if (cherris < 0)    {
                        //cout<<" less than zero "<<endl;
                        continue;
                    }
                    dp[i][j] =  cherris + grid[i][k-i];
                    if (i != j) dp[i][j] += grid[j][k-j];
                    //cout<<" dp ij "<<dp[i][j]<<endl;
                }
            }
        }
        return max(0, dp[N-1][N-1]);
    }

};


/*
两个人同时从（0，0） 出发，到达(N-1, N-1),
k = 代表i+j 长度
dp[i][j] 代表第一个人到i,k-i, 第二个人到j,k-j, 一共可以pick up cherry
dp[i][j] = max( 
    dp[i][j], //person1 向右走，person2 向右走
    dp[i-1][j]), //person1 向下走, person2 向右走
    dp[i][j-1]), //person1 向右走，person2 向下走
    dp[i-1][j-1]), //person1 向下走，person2 向下走
)

example 1,
grid 
    1  1  -1
    1  -1  1
    -1  1  1

after k=1 dp,        after k = 2 dp, 
    2  3  -1         -1(都在(0,2))       -1 (在(0,2),(1,1))   -1  (在(0,2),(2,0)) 
    3  2  -1         -1(在(1,1),(0,2))  -1  (都在(1,1))       -1  (在(1,1),(2,0)) 
    -1 -1 -1         -1(在(2,0),(0,2))   -1 (在(2,0), (1,1))  -1（都在（2，0)）




example 2, 
grid 
    1  1  -1
    1  -1  1
    1  1  1
after k=1 dp,        after k = 2 dp, 
    2  3  -1         -1   -1    -1  
    3  2  -1         -1   -1    -1
    -1 -1 -1         -1   -1    3 

after k=3 dp,        after k = 4 dp, 
    -1  -1  -1         -1   -1    -1  
    -1  -1  -1         -1   -1    -1
    -1  -1   4         -1   -1    5 

比如 k = 3 时候 dp[2][1]  代表此刻 person1 在(2,1), person2 在(1,2)
dp[2][1] 来自于 k=2时  = max( 
    dp[2][1],   k=2时person1 在(2,0), person2 在(1,1) 从k=2 到k=3, person1, person2 都向右走一步
    dp[1][1],   k=2时person1 在(1,1), person2 在(1,1) 从k=2 到k=3, person1 向下一步, person2 向右一步
    dp[1][0],   k=2时person1 在(1,1), person2 在(0,2) 从k=2 到k=3, person1 向下一步, person2 向下一步
    dp[2][0],   k=2时person1 在(2,0), person2 在(0,2) 从k=2 到k=3, person1 向右一步, person2 向下一步
 )


*/
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N, -1));
        dp[0][0] = grid[0][0];
        for(int k = 1; k<=2*N-2; k++){
            for(int i = min(k, N-1); i>=0; i--){
                if(k-i>=N) continue;
                for(int j = min(k,N-1); j>=0; j--){
                    if (k - j >= N || grid[i][k - i] < 0 || grid[j][k - j] < 0) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cherry = dp[i][j];
                    if(i>0) cherry = max(dp[i-1][j], cherry);
                    if(j>0) cherry = max(dp[i][j-1], cherry);
                    if(i>0 && j>0) cherry = max(dp[i-1][j-1], cherry);
                    if(cherry<0) continue;
                    cherry += grid[i][k-i];
                    if(j!=i) cherry += grid[j][k-j];
                    dp[i][j] = cherry;
                }
            }
        }
        return max(0, dp[N-1][N-1]);
    }
};

