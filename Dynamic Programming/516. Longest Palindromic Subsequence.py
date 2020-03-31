"""
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


"""
class Solution:
    def longestPalindromeSubseq(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if n == 0: return 0;
        dp = [[0 for _ in range(n)] for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i][i] = 1
            for j in range(i+1, n):
                if s[i] == s[j]: 
                    dp[i][j] = dp[i+1][j-1] +2
                else: 
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        #print(dp)
        return dp[0][n-1]



class Solution:
    def longestPalindromeSubseq(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if s == s[::-1]: return n  #加这个快很多
        if n == 0: return 0;
        dp = [0 for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i] = 1
            prev = 0
            for j in range(i+1, n):
                prev, dp[j] = dp[j], prev+2 if s[i] == s[j] else max(dp[j],dp[j-1])
        #print(dp)
        return dp[-1]
