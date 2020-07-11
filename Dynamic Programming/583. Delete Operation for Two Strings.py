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
        
# Bottom-up
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        dp = [[0] * (n + 1) for i in range(m + 1)]
        for i in range(m):
            for j in range(n):
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j], dp[i][j] + (word1[i] == word2[j]))
        return m + n - 2 * dp[m][n]

# Top-Down
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        memo = {}
        def topDown(i, j):
            if (i, j) not in memo:
                if i == 0 or j == 0:
                    ans = i if i else j 
                elif word1[i-1] == word2[j-1]:
                    ans = topDown(i-1, j-1)
                else:
                    ans = 1 + min(topDown(i-1, j), topDown(i, j-1))
                memo[(i, j)] = ans
            return memo[(i, j)]
        return topDown(len(word1), len(word2))

# Top-Down
# i == len(A) or j == len(B), one of the strings is empty, so the answer is just the sum of the remaining lengths.
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        memo = {}
        def topDown(i, j):
            if (i, j) not in memo:
                if i == len(word1) or j == len(word2):
                    ans = len(word1) + len(word2) - i - j
                elif word1[i] == word2[j]:
                    ans = topDown(i+1, j+1)
                else:
                    ans = 1 + min(topDown(i+1, j), topDown(i, j+1))
                memo[(i, j)] = ans
            return memo[(i, j)]
        return topDown(0, 0)