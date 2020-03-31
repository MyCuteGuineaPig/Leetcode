/*
712. Minimum ASCII Delete Sum for Two Strings

Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
Note:

0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].


*/


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