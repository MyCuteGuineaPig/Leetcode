
/*
583. Delete Operation for Two Strings

Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

*/

/*
         s1 s e a 
     s2  0  1 2 3 
     e   1  2 1 2
     a   2  3 2 1  
     t   3  4 3 2
 
    如果s[i]!=s[j]  dp[i][j] = 1+min(dp[i-1][j], dp[i][j-1]) =  dp[i][j-1] + 1 横向移动，代表删除的是s1
    如果s[i]!=s[j]  dp[i][j] = 1+min(dp[i-1][j], dp[i][j-1]) =  dp[i-1][j] + 1 纵向移动，代表删除的是s2

*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<vector<int>>dp(2, vector<int>(n2+1,INT_MAX));
        for(int i = 0; i<=n1; i++)
            for(int j = 0, k = i%2; j<=n2; j++)
                dp[k][j] =  i == 0 || j ==0 ? (i == 0? j: i) : word1[i-1] == word2[j-1] ? dp[k^1][j-1]: 1+min(dp[k^1][j], dp[k][j-1]); 
        return dp[n1%2][n2];
    }
};