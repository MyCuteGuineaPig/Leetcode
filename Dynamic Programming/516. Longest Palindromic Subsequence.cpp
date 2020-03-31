

/*
516. Longest Palindromic Subsequence

Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".


*/


class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>>dp(s.size(),vector<int>(s.size(),0));
        for(int j = 0; j<s.size();j++){
            dp[j][j] = 1;      
            for(int i = j-1; i>=0;i--){
                if(s[j]==s[i]){
                    if(j-i==1)
                        dp[i][j] = 2;
                    else 
                        dp[i][j] = max(dp[i][j],dp[i+1][j-1]+2);
                }
                else{
                    if (i<s.size())
                        dp[i][j] = max(dp[i][j],dp[i+1][j]);
                    if (j>0)
                        dp[i][j] = max(dp[i][j],dp[i][j-1]);
                }
            }
            
        }
        return dp[0][s.size()-1];
    }
};


class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>>dp(s.size(),vector<int>(s.size(),0));
        for(int j = 0; j<s.size();j++){
            dp[j][j] = 1;      
            for(int i = j-1; i>=0;i--){
                if(s[j]==s[i])
                    dp[i][j] = dp[i+1][j-1]+2;
                else
                    dp[i][j] = max(dp[i][j-1],dp[i+1][j]);
            }
        }
        return dp[0][s.size()-1];
    }
};

/*
把space 减成O(N), O(N)比O(N*N) 快的多
*/

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>>dp(2,vector<int>(s.size(),0));
        for(int j = 0; j<s.size();j++){
            dp[j%2][j] = 1;      
            for(int i = j-1; i>=0;i--){
                if(s[j]==s[i])
                    dp[j%2][i] = dp[(j+1)%2][i+1]+2;
                else
                    dp[j%2][i] = max(dp[(j+1)%2][i],dp[j%2][i+1]);
            }
        }
        return dp[(s.size()-1)%2][0];
    }
};


class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int N = s.size();
        vector<int> m(N, 0);
        for (int i=N-1; i>=0; --i) {
            m[i] = 1;
            int b = 0;
            for (int j=i+1; j<N; ++j) {
                int t = m[j];
                m[j] = s[i]==s[j]? b+2: max(m[j], m[j-1]);
                b = t;
            }
        }
        return m[N-1];
    }
};

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<int>dp(s.size(),0);
        for(int i = s.size()-1; i>=0; i--){
            dp[i] = 1;
            int prev = 0; //track i+1 j-1的值
            for(int j = i+1; j<s.size();j++){
                int temp = dp[j];
                dp[j] = (s[i]==s[j]) ? prev + 2 : max(dp[j],dp[j-1]); //m[j-1] 代表[i][j-1] dp[j]代表[i+1][j]上一个到j的结果
                prev = temp;
            }
        }
        return dp[s.size()-1];
    }
};