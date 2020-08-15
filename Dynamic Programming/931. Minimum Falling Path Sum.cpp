
/*
2020 Bottom-up
Complexity: O(m*n)
space:  O(n)
*/

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        vector<int>dp(m);
        for(int i = 0; i<n; ++i){
            int prev = 100001;
            for(int j = m-1; j>=0; --j){
                int tmp = dp[j];
                dp[j] += A[i][j];
                if(i>0){
                    if(j != m-1)
                        dp[j] = min(dp[j], prev+A[i][j]);
                    if(j!=0)
                        dp[j] = min(dp[j], dp[j-1] + A[i][j]);
                }
                prev = tmp;
            }
        }
        
        int res = numeric_limits<int>::max();
        for(auto i: dp)
            res = min(i, res);
        return res;
    }
};


//2020 TopDown
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        unordered_map<int,unordered_map<int,int>>dp;
        int res = numeric_limits<int>::max();
        for(int i = 0; i<m; ++i)
            res = min(res, topDown(n-1, i, A, dp));
        return res;
    }
    
    int topDown(int i, int j, vector<vector<int>>& A, unordered_map<int,unordered_map<int,int>>&dp){
        if(j<0 || j>=A[0].size())
            return 100001;
        if(i == 0)
            return A[0][j];
        if(dp.count(i) && dp[i].count(j))
            return dp[i][j];
        return dp[i][j] = A[i][j]+ min(min(topDown(i-1, j-1, A, dp),
                                      topDown(i-1, j, A, dp)),
                                     topDown(i-1, j+1, A, dp));
    }
};


class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
      for (auto i = 1; i < A.size(); ++i)
        for (auto j = 0; j < A.size(); ++j)
          A[i][j] += min({ A[i-1][j], A[i-1][max(0,j-1)], A[i-1][min((int)A.size()-1,j+1)] });
      return *min_element(begin(A[A.size() - 1]), end(A[A.size() - 1]));
    }
};