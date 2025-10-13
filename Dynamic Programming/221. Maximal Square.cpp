class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size()==0) return 0;
        vector<vector<int>>dp(matrix.size(),vector<int>(matrix[0].size(),0));
        int maxre = 0;
        
        for(int i = 0; i<matrix.size();i++){
            for(int j = 0; j<matrix[i].size();j++){
                if(i == 0) 
                {
                    dp[0][j] = matrix[0][j] - '0';
                    maxre = max(maxre,dp[0][j]);
                }
                if(j==0){
                    dp[i][0] = matrix[i][0] - '0';
                    maxre = max(maxre,dp[i][0]);
                }
                else if(i!=0 && j!=0 && matrix[i][j] == '1'){
                    dp[i][j] = min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1; //需要三个min的原因
                    /*
                    
                    [["1","1","1","1","0"],
                     ["1","1","1","1","0"],
                     ["1","1","1","1","1"],
                     ["1","1","1","1","1"],
                     ["0","0","1","1","1"]]
                    答案是 16, 如果dp[i][j] = dp[i-1][j-1]+1;  结果是25
                    */


                    maxre = max(maxre,dp[i][j]);
                }
            }
        }
        return maxre*maxre;
    }
};


//2025
/*
需要 dp[i-1][j-1]
比如 [["0","0","1"],["0","1","1"],["1","1","1"]]


 */
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>>dp(n, vector<int>(m));
        int res = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j) {
                if(matrix[i][j] ==  '0' ) continue;
                if (i == 0 || j == 0) dp[i][j] = 1;
                else 
                    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1 ;
                res = max(res, dp[i][j]*dp[i][j]);
            } 
        }
        
        return res;
    }
};



/*
DP(i,j) 记录的是到i,j 为止组成最大正方形的边长，只要(i-1,j),(i,j-1),(i-1,j-1)任何一个点是0，都不能在(i,j)组成边长为2的正方形
*/
static int x = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size()==0) return 0;
        int n = matrix.size(), m = matrix[0].size(), res = 0;
        vector<int>dp(m+1, 0);
        for(int i = 0; i<n; i++){
            for(int j = 0, prev = 0; j<m; j++){
                int temp = dp[j+1]; 
                if(matrix[i][j]=='1'){
                    dp[j+1] = min(min(dp[j],prev),dp[j+1])+1;
                    res = max(res, dp[j+1]);
                }
                else dp[j+1] = 0;
                prev = temp;
            }
        }
        return res*res;
    }
    
};

/*

[["0","0","0","1"],
 ["1","1","0","1"],
 ["1","1","1","1"],
 ["0","1","1","1"],
 ["0","1","1","1"]]

 [["1","0","1","0"],
 ["1","0","1","1"],
 ["1","0","1","1"],
 ["1","1","1","1"]]

[["1","0","1","0","0"],
["1","0","1","1","1"],
["1","1","1","1","1"],
["1","0","0","1","0"]]

[["0","1","1","0","1"],
["1","1","0","1","0"],
["0","1","1","1","0"],
["1","1","1","1","0"],
["1","1","1","1","1"],
["0","0","0","0","0"]]

*/