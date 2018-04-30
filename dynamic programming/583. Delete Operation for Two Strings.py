"""
583. Delete Operation for Two Strings

"""

class Solution:
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        n, m = len(word1), len(word2)
        dp = [[0,]*(n+1) for _ in range(m+1)]
        for i in range(n):
            dp[0][i+1] = i+1;
        for i in range(m):
            dp[i+1][0] = i+1;    
        for i in range(m):
            for j in range(n):
                dp[i+1][j+1] = dp[i][j] if word1[j] == word2[i] else min(dp[i][j+1], dp[i+1][j])+1
        #print(dp)
        return dp[-1][-1]

class Solution:
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        n, m = len(word1), len(word2)
        dp = [0,]*(n+1)
        for i in range(n):
            dp[i+1] = i+1;
        for i in range(m):
            dp[0] = i+1
            prev = i
            for j in range(n):
                prev, dp[j+1] = dp[j+1], prev if word1[j] == word2[i] else min(dp[j], dp[j+1])+1
        #print(dp)
        return dp[-1]
        