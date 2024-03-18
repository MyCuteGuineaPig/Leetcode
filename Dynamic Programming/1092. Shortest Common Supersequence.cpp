class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        string lcs = get_lcs(str1, str2);
        int i = 0, j = 0;
        string res("");
        for(auto c: lcs){
            while(str1[i]!=c){
                res += str1[i++];
            } 
            while(str2[j]!=c){
                res += str2[j++];
            }
            res += c; ++i; ++j; 
        }
        return res + str1.substr(i) + str2.substr(j);
    }

    string get_lcs(const string& str1, const string& str2){
        int n = str1.size(), m = str2.size();
        vector<vector<string>>dp(2, vector<string>(m+1, ""));
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if (str1[i] == str2[j]){
                    dp[(i + 1)%2][j+1] = dp[i%2][j] + str1[i];
                } else {
                    dp[(i + 1)%2][j+1] = dp[(i + 1)%2][j].size() > dp[i%2][j+1].size()? dp[(i + 1)%2][j] : dp[i%2][j+1];
                }
            }
        }
        return dp[n%2][m];
    }
};


class Solution {
public:
    string shortestCommonSupersequence(string a, string b) {
        int dp[1001][1001] = {}, m = a.size(), n = b.size();
        for (int i = 0; i < m; ++i) // DP
            for (int j = 0; j < n; ++j)
                dp[i + 1][j + 1] = a[i] == b[j] ? 
                    dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
        string res;
        while (m && n) // Backtracking
            if (dp[m][n] == dp[m - 1][n])
                res += a[--m]; // Character only in a
            else if (dp[m][n] == dp[m][n - 1])
                res += b[--n]; // Character only in b
            else
                res += min(a[--m], b[--n]); // Shared character in a & b
        return a.substr(0, m) + b.substr(0, n) + string(rbegin(res), rend(res));
    }
};