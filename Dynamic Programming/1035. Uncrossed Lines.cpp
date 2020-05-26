//Top-Down
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        unordered_map<int,vector<int>>mp;
        for(int i = 0; i<B.size(); ++i)
            mp[B[i]].push_back(i);
        unordered_map<int,unordered_map<int,int>>dp;
        return helper(mp,dp, A, 0, 0);
    }
    
    int helper(unordered_map<int,vector<int>>&mp, unordered_map<int,unordered_map<int,int>>&dp, const vector<int>& A, int Astart, int Bstart){
        if(dp.count(Astart) && dp[Astart].count(Bstart))
            return dp[Astart][Bstart];
        if(Astart >= A.size())
            return 0;
        
        int cur = 0;
        for(int i = Astart; i<A.size(); ++i){
            for(auto nxt: mp[A[i]]){
                if(nxt >= Bstart){
                    cur = max(cur, helper(mp, dp, A, i+1, nxt+1)+1);
                    break;
                }   
            }
        }
        return dp[Astart][Bstart] = cur;
    }
};





//Bottom-up
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        vector<vector<int>>dp(A.size()+1, vector<int>(B.size()+1));
        for(int i = 0; i<A.size(); ++i){
            for(int j = 0; j<B.size(); ++j){
                dp[i+1][j+1] = max(dp[i][j] + static_cast<int>(A[i] == B[j]), max(dp[i+1][j], dp[i][j+1]));
            }
        }
        return dp[A.size()][B.size()];
    }
};

class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        if (A.size() < B.size()) {
            return maxUncrossedLines(B, A);
        }
        vector<vector<int>> dp(2, vector<int>(B.size() + 1));
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                dp[(i + 1) % 2][j + 1] = max(dp[i % 2][j] + static_cast<int>(A[i] == B[j]),
                                             max(dp[i % 2][j + 1], dp[(i + 1) % 2][j]));
            }
        }
        return dp[(A.size()) % 2][B.size()];
    }
};


class Solution {
public:
    int helper(vector<vector<int>>&dp, const vector<int>& A, const vector<int>& B, int i, int j){
        if(i >= A.size() || j>=B.size())
            return 0;
        if(dp[i][j] >= 0)
            return dp[i][j];
        if(A[i] == B[j])
            return dp[i][j] = 1 + helper(dp, A, B, i+1, j+1); //dp[i+1][j+1] >= dp[i+1][j],   dp[i+1][j+1] = dp[i][j+1]
        return dp[i][j] = max(helper(dp, A, B, i+1, j), helper(dp, A, B, i, j+1));
    }
    
    
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
      vector<vector<int>> dp(A.size(), vector<int>(B.size(), -1));
      return helper(dp, A, B, 0, 0);
    }
};


class Solution {
public:
    int dfs(vector<int>& A, vector<int>& B, int i, int j, vector<vector<int>> &dp) {
      if (i >= A.size() || j >= B.size()) return 0;
        
      if (dp[i][j] != -1) return dp[i][j];
      auto nj = j;
      while (nj < B.size() && B[nj] != A[i]) ++nj;
      return dp[i][j] = max(dfs(A, B, i + 1, j, dp), (nj < B.size() ? 1 : 0) + dfs(A, B, i + 1, nj + 1, dp));
    }
    
    
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
      vector<vector<int>> dp(A.size(), vector<int>(B.size(), -1));
      return dfs(A, B, 0, 0, dp);
    }
};