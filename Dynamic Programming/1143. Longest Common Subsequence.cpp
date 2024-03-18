class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n  = text1.size(), m = text2.size();
        vector<vector<int>>dp(n+1, vector<int>(m+1));
        for(int i = 0; i<n; ++i){
            for(int j = 0; j < m ; ++j){
                dp[i+1][j+1] = (text1[i] == text2[j]? dp[i][j] + 1: max(dp[i+1][j], dp[i][j+1]));
            }
        }
        return dp[n][m];
    }
};


class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
      int n=s1.length(),m=s2.length();
      vector<int> prev(m+1,0);
      vector<int> curr(m+1,0);
      for(int i=1;i<=n;i++)
      {
        for(int j=1;j<=m;j++)
        {
            if(s1[i-1]==s2[j-1])
            curr[j]=1+prev[j-1];
            else
            curr[j]=max(prev[j],curr[j-1]);
        }
        prev=curr;
      }
      return curr[m];
    }
};