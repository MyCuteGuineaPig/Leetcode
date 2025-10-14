/*
dp[i][j][k] 代表从boxes[i:j] 之后k个与boxes[j] 一样color ball，所得最大的count数



the memoization matrix to be memo[l][r][k], the largest number we can get using lth to rth (inclusive) 
boxes with k same colored boxes as rth box appended at the end. Example, 
memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A,A,A] with b_r==A.

The transition function is to find the maximum among all b_i==b_r for i=l,...,r-1:
memo[l][r][k] = max(memo[l][r][k], memo[l][i][k+1] + memo[i+1][r-1][0])

[1, 3, 2, 2, 2, 3, 4, 3, 1] 
比如当j = 7, 与pos = 1, 5 都是3, call recursion, 
call dfs(i=0, j = 1, k = 1)
call dfs(i=0, j= 5, k = 1) 但是这里面还有recusion，因为j=5 和pos = 1 又相同， call dfs(i=0, j= 1, k = 2)  


*/


// Top-Down
int dp[102][102][102];
class Solutiaon {
public:
    int c[102], len[102];
    int removeBoxes(vector<int>& boxes) {
        memset(c,0,sizeof(c));
        memset(len,0,sizeof(len));
        memset(dp,-1,sizeof(dp));
        int n = 0;
        for(int i = 0; i<boxes.size(); i++){
            if(i!=0 && boxes[i]==c[n]){
                len[n]++;
            }
            else{
                c[++n] = boxes[i];
                len[n] = 1;
            }
        }
 
        return dfs(1,n, 0);
    }
    
    int dfs(int i, int j, int k){
        if(dp[i][j][k]!=-1)
            return dp[i][j][k];
        if(i>j)
            return 0;
        dp[i][j][k] = dfs(i, j-1, 0) + (len[j]+k)*(len[j]+k);
        for(int pos = i; pos<j; pos++){
            if(c[j] == c[pos])
                dp[i][j][k] = max(dp[i][j][k], dfs(i,pos,k+len[j])+dfs(pos+1, j-1, 0));
        }
        return dp[i][j][k];
    }
};


const int maxn = 105;
int d[maxn][maxn][maxn];

class Solution {
private:
    int c[maxn], len[maxn];
public:
    int dfs(int i, int j, int k) {
        if (d[i][j][k] != -1) {
            return d[i][j][k];
        }
        if (i > j) {
            return 0;
        }
        
        d[i][j][k] = dfs(i, j - 1, 0) + (len[j] + k) * (len[j] + k);
        for (int pos = i; pos < j; pos++) {
            if (c[pos] == c[j]) {
                int before = dfs(i, pos, len[j] + k);
                int after = dfs(pos + 1, j - 1, 0);
                d[i][j][k] = max(d[i][j][k], before + after);
            }
        }
        return d[i][j][k];
    }

    int removeBoxes(vector<int>& boxes) {
        int n = 0;
        memset(c, 0, sizeof(c));
        memset(len, 0, sizeof(len));
        memset(d, -1, sizeof(d));
        for (int i = 0; i < boxes.size(); i++) {
            if (i == 0 || boxes[i] != boxes[i - 1]) c[++n] = boxes[i], len[n] = 1;
            else len[n]++;
        }
        return dfs(1, n, 0);
    }
};


/*
dp[i][j][k]: 表示 boxes[i,j] 可获得maximum point 通过remove 有 k个boxes 有一样的color 在boxes[i] 左侧

Let dp(i, j, k) = the maximum value of removing boxes if we have k extra boxes of color A[i] to the left of boxes[i: j]. 

1. dp[i][i-1][k] = 0, no boxes, so no point 
2. dp[i][i][k] = (k+1)*(k+1):  only one box left in the subarray, 左侧有k个一样颜色的盒子, number是(k+1)*(k+1)
3. dp[i][j][k] 如果 boxes[i] = boxes[m] (i < m < k): 
              = max(dp[i][j][k], dp[i+1][m-1][0] + dp[m][j][k+1])

 */
class Solution {
public:
    int n;
    vector<vector<vector<int>>>dp;
    int removeBoxes(vector<int>& boxes) {
        n = boxes.size();
        dp.resize(n, vector<vector<int>>(n, vector<int>(n)));
        return helper(boxes, 0, n-1, 0);
    }
    
    int helper(const vector<int>& boxes, int i, int j, int k){
        if(i>j) return 0;
        if(dp[i][j][k]>0)
            return dp[i][j][k];
        while(i<j && boxes[j-1] == boxes[j]){ k++; j--;}
        dp[i][j][k] = helper(boxes, i, j-1, 0)+(k+1)*(k+1);
        for(int x = i; x<j; x++){
            if(boxes[j] == boxes[x]){
                dp[i][j][k] = max(dp[i][j][k],helper(boxes, i, x, k+1)+helper(boxes, x+1, j-1, 0));
            }
        }
        return dp[i][j][k];
    }
    
};

//Bottom-up
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
    int n = boxes.size();
    vector<vector<vector<int>>>dp(n, vector<vector<int>>(n, vector<int>(n)));
    	
    for (int j = 0; j < n; j++) {
    	for (int k = 0; k <= j; k++) {
    	    dp[j][j][k] = (k + 1) * (k + 1);
    	}
    }
    	
    for (int l = 1; l < n; l++) {
    	for (int j = l; j < n; j++) {
    	    int i = j安全· - l;
    	        
    	    for (int k = 0; k <= i; k++) {
    	        int res = (k + 1) * (k + 1) + dp[i + 1][j][0];
    	            
    	        for (int m = i + 1; m <= j; m++) {
    	            if (boxes[m] == boxes[i]) {
    	                res = max(res, dp[i + 1][m - 1][0] + dp[m][j][k + 1]);
    	            }
    	        }
    	            
    	        dp[i][j][k] = res;
    	    }
    	}
    }
    
    return (n == 0 ? 0 : dp[0][n - 1][0]);
    }
};



/*

dp[i][j][k] 代表从boxes[i:j] 之后k个与boxes[j] 一样color ball，所得最大的count数
The idea is to use a 3D DP array dp[i][j][k] to represent the maximum points that
 can be obtained by removing boxes from index i to j (inclusive) with k boxes of 
 the same color as boxes[j] adjacent to the right of j.


 https://leetcode.com/problems/remove-boxes/editorial/

dp[l][r][k]=dp[l][r−1][0]+(k+1)∗(k+1)

 dp[l][r][k]=max(dp[l][r][k],dp[l][i][k+1]+dp[i+1][r-1][0]).

 */


//2025 top-down
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
    int n = boxes.size();
    vector<vector<vector<int>>>dp(n, vector<vector<int>>(n, vector<int>(n,0)));

    auto f = [&](this auto&& f, int i, int j, int k){
        if (i > j) 
            return 0;
        while (i < j && boxes[j] == boxes[j-1]){
            --j;
            ++k;
        }
        if (dp[i][j][k] != 0) return dp[i][j][k];
        dp[i][j][k] = f(i, j-1, 0) + (k+1)*(k+1);

        for(int m = i; m < j; ++m){
            if (boxes[m] == boxes[j]) 
                dp[i][j][k] = max(dp[i][j][k], f(m+1, j-1, 0) + f(i, m, k+1));
        }
        return dp[i][j][k];
    };
    return f(0, n-1, 0);
    }
};


//2025 Bottom-up
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(n, vector<int>(n,0)));
        for(int i = 0; i < n; ++i){
            for(int k = 0; k < n-i; ++k)
                dp[i][i][k] = (k+1)*(k+1);
        }

        for(int i = n-2; i >=0; --i){
            for(int j = i + 1; j < n; ++j){
                for(int k = 0; k <n-j; ++k){
                    dp[i][j][k] = dp[i][j-1][0] + (k+1)*(k+1);
                    for(int m = i; m < j ; ++m){
                        if (boxes[m] == boxes[j])
                            dp[i][j][k] = max(dp[i][j][k], dp[i][m][k+1] + dp[m+1][j-1][0]);
                    }
                }
            }
        }
        return dp[0][n-1][0];
    }
};