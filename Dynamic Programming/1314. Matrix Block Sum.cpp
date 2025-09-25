class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>>dp(m+1, vector<int>(n+1));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j) {
                dp[i+1][j+1] = dp[i+1][j] + dp[i][j+1] + mat[i][j] - dp[i][j];
            }
        }

        vector<vector<int>>res(m, vector<int>(n));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j) {
                int row1 = max(0, i - k);
                int col1 = max(0, j - k);
                int row2 = min(m-1, i+k);
                int col2 = min(n-1, j + k);
                res[i][j] = dp[row2+1][col2+1] - dp[row2+1][col1] - dp[row1][col2+1] + dp[row1][col1];
            }
        }
        return res;
    }
};