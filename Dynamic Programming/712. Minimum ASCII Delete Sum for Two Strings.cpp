//Bottom-up
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>>dp(s1.size()+1,vector<int>(s2.size()+1));
        for(int i = 0; i<=s1.size(); i++){
            for(int j = 0; j<=s2.size();j++){
                if(i == 0 && j!=0)
                    dp[i][j] = dp[i][j-1] + s2[j-1];
                else if(i != 0 && j==0)
                    dp[i][j] = dp[i-1][j] + s1[i-1];
                else if(i>0 && j>0)
                    dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1]: min(dp[i][j-1]+s2[j-1], dp[i-1][j] + s1[i-1]);
            }
        }
        return dp[s1.size()][s2.size()];
    }
};


//Bottom-up
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<int>>dp(n1+1, vector<int>(n2+1));
        int ord = 0;
        for(int i = 0; i<n1; ++i)
            ord += s1[i];

        for(int j = 0; j<n2; ++j)
            ord += s2[j];
        
        for(int i = 0; i<n1; ++i){
            for(int j = 0; j<n2; ++j){
                if(s1[i] == s2[j])
                    dp[i+1][j+1] = dp[i][j] + s1[i];
                else
                    dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
        return ord - dp[n1][n2]*2;
    }
};

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        vector<vector<int>>dp(2,vector<int>(s2.size()+1));
        for(int i = 0; i<=s1.size(); i++){
            for(int j = 0, k = i%2; j<=s2.size();j++){
                if(i == 0 && j!=0)
                    dp[k][j] = dp[k][j-1] + s2[j-1];
                else if(i != 0 && j==0)
                    dp[k][j] = dp[k^1][j] + s1[i-1];
                else if(i>0 && j>0)
                    dp[k][j] = (s1[i-1] == s2[j-1]) ? dp[k^1][j-1]: min(dp[k][j-1]+s2[j-1], dp[k^1][j] + s1[i-1]);
            }
        }
        return dp[s1.size()%2][s2.size()];
    }
};


//O(n) space
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> dp(n+1, 0);
        for (int j = 1; j <= n; j++)
            dp[j] = dp[j-1]+s2[j-1];
        for (int i = 1; i <= m; i++) {
            int t1 = dp[0];
            dp[0] += s1[i-1];
            for (int j = 1; j <= n; j++) {
                int t2 = dp[j];
                dp[j] = s1[i-1] == s2[j-1]? t1:min(dp[j]+s1[i-1], dp[j-1]+s2[j-1]);
                t1 = t2;
            }
        }
        return dp[n];
    }
};

// 2020 Top-Down
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<int>>dp(n1+1, vector<int>(n2+1, -1));
        return topDown(dp, s1, s2, n1, n2);
    }
    
    int topDown( vector<vector<int>>&dp, const string& s1, const string&s2, int i, int j){
        if(i == 0 && j == 0)
            return 0;
        if(dp[i][j] != -1)
            return dp[i][j];
        int res = numeric_limits<int>::max();
        if(i>0 && j > 0 && s1[i-1] == s2[j-1])
            res = min(res, topDown(dp, s1, s2, i-1, j-1));
        if(i)
            res = min(res, topDown(dp, s1, s2, i-1, j) + s1[i-1]);
        if(j)
            res = min(res, topDown(dp, s1, s2, i, j-1) + s2[j-1]);
        return dp[i][j] = res;
    }
};