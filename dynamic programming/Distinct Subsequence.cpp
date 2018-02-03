/*

115. Distinct Subsequences
https://leetcode.com/problems/distinct-subsequences/description/


Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.



*/


/*
Well, a dynamic programming problem. Let's first define its state dp[i][j] to be the number of distinct subsequences of t[0..i - 1] in s[0..j - 1]. 
Then we have the following state equations:

General case 1: dp[i][j] = dp[i][j - 1] if t[i - 1] != s[j - 1];
General case 2: dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1] if t[i - 1] == s[j - 1];
Boundary case 1: dp[0][j] = 1 for all j;
Boundary case 2: dp[i][0] = 0 for all positive i.
Now let's give brief explanations to the four equations above.

If t[i - 1] != s[j - 1], the distinct subsequences will not include s[j - 1] and 
thus all the number of distinct subsequences will simply be those in s[0..j - 2], 
which corresponds to dp[i][j - 1];
If t[i - 1] == s[j - 1], the number of distinct subsequences include two parts: 
those with s[j - 1] and those without;
An empty string will have exactly one subsequence in any string :-)
Non-empty string will have no subsequences in an empty string.
Putting these together, we will have the following simple codes (just like translation :-)):


*/



class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.length(), n = s.length();
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
        for (int j = 0; j <= n; j++) dp[0][j] = 1;//如果t string 长度为0，只能把所有的s全部都delete 掉才行，所以都是1
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= m; i++){
                //cout<<" i "<<i <<" j "<<j<<" dp[i][j - 1] "<<dp[i][j - 1]<<endl;
                
                //if(t[i - 1] == s[j - 1]){
                //    cout<<" dp[i - 1][j - 1] "<<dp[i - 1][j - 1]<<" t[i-1] "<<t.substr(0,i)<<" s[j - 1] "<<s.substr(0,j)<<endl;
                //}
                dp[i][j] = dp[i][j - 1] + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);
                //cout<<"final dp "<<dp[i][j]<<endl;
            }
                
        return dp[m][n];
    }
};  