/*
注意题目条件是 N x N Matrix

两个人同时从(0，0) 出发，到达(N-1, N-1), k为此时距(0,0)距离,

dp[i][j]代表 距离为k时person1到i,k-i, person2到j,k-j, 一共可以pick up最多cherry，

dp[i][j] = grid[i][k-i]+grid[j][k-j]+max(
        dp[i][j],     person1 向右走， person2 向右走
        dp[i-1][j],   person1 向下走, person2 向右走
        dp[i][j-1]),  person1 向右走，person2 向下走
        dp[i-1][j-1])  person1 向下走，person2 向下走

 */

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N, -1));
        dp[0][0] = grid[0][0];
        for (int k = 1, maxK = 2*N-2; k <= maxK; ++k) {
            for (int i = min(N-1, k); i >= max(0, k-N+1); --i) { //只能是倒叙 不能是正序, 
            //比如 k = 5,  dp[2][3] = grid[2][3] + grid[3][2] + max(dp[2][3], dp[1][3], dp[2][2], dp[1][2])
            // 大的i,j 取决于小的i,j (上次k的结果)
\
                for (int j = min(N-1, k); j >= max(0, k-N+1); --j) {
                    if (grid[i][k - i] < 0 || grid[j][k - j] < 0) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cherris = dp[i][j];//person1 向右走，person2 向右走
                    
                    if (i > 0)  cherris = max(cherris, dp[i-1][j]);//[i-1][j] person1 向下走，person2 向右走
                    if (j > 0)  cherris = max(cherris, dp[i][j-1]);//[i][j-1] person1 向右走，person2 向下走
                    if (i > 0 && j > 0)  cherris = max(cherris, dp[i-1][j-1]);//person1 向下走，person2 向下走
                    
                    if (cherris < 0)    {
                        continue;
                    }
                    dp[i][j] =  cherris + grid[i][k-i];
                    if (i != j) dp[i][j] += grid[j][k-j];
                }
            }
        }
        return max(0, dp[N-1][N-1]);
    }

};

// Top-Down

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int N = grid.size();
        vector<vector<vector<int>>>dp(N,vector<vector<int>>(N, vector<int>(N,-2)));
        dp[0][0][0] = grid[0][0];
        return max(topDown(dp, grid, N, N-1, N-1, N-1),0);
    }
    
    
    int topDown(vector<vector<vector<int>>>&dp, const vector<vector<int>>& grid, int N, int r1, int c1, int r2){
        int c2 = r1 + c1 - r2;
        if(r1 <0 || r1 >= N || c1 <0 || c1 >= N || r2 <0 || r2 >= N || c2 <0 || r2 >= N || grid[r1][c1] == -1 || grid[r2][c2] == -1){
            return -1;
        }
        if(dp[r1][c1][r2] >= -1)
            return dp[r1][c1][r2];
        int res = -1;
        res =  max(res, topDown(dp, grid, N, r1-1, c1, r2-1));
        res =  max(res, topDown(dp, grid, N, r1-1, c1, r2));
        res =  max(res, topDown(dp, grid, N, r1, c1-1, r2-1));
        res =  max(res, topDown(dp, grid, N, r1, c1-1, r2));
        
        //cout<<" r1 "<<r1<<" c1 "<<c1<<" r2 "<<r2<<" c2 "<<c2<<" res "<<res;
        if(res == -1)
            dp[r1][c1][r2] = res;
        else 
            dp[r1][c1][r2] = res + grid[r1][c1] + (r1 == r2 ? 0: grid[r2][c2]);
        //cout<<" dp "<< dp[r1][c1][r2]<<endl;
        return dp[r1][c1][r2];
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






//Brute Force

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<vector<int>>>dp(n + 1, vector<vector<int>>(n+1, vector<int>(n+1,numeric_limits<int>::min())));
        
        dp[1][1][1] = grid[0][0];
        for(int x1 = 1; x1 <= n; x1++){
            for(int y1 = 1; y1 <= n; y1++){
                for(int x2 = 1; x2 <= n; x2++){
                    int y2 = x1 + y1 - x2;
                    if(dp[x1][y1][x2] > 0 || y2 < 1 || y2 > n || grid[x1 - 1][y1 - 1] == -1 || grid[x2 - 1][y2 - 1] == -1){
                        continue;
                        // have already detected || out of boundary || cannot access 
                    }
                    int cur = max(max(dp[x1 - 1][y1][x2], dp[x1 - 1][y1][x2 - 1]), max(dp[x1][y1 - 1][x2], dp[x1][y1 - 1][x2 - 1]));
                    if(cur < 0){
                        continue;
                    }
                    dp[x1][y1][x2] = cur + grid[x1 - 1][y1 - 1];
                    if(x1 != x2){
                        dp[x1][y1][x2] += grid[x2 - 1][y2 - 1];
                    }
                }
            }
        }
        return dp[n][n][n] < 0 ? 0 : dp[n][n][n];
    }

};