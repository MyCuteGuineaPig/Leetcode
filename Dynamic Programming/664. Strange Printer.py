#2020
class Solution:
    def strangePrinter(self, s: str) -> int:
        n = len(s)
        if n == 0: return 0
        dp = [[n+1,]*(n) for _ in range(n)]
        for r in range(n):
            dp[r][r] = 1
            for l in range(r-1, -1, -1):
                if s[l] == s[r]:
                    dp[l][r] = dp[l][r-1]
                else:
                    for k in range(l, r):
                        dp[l][r] = min(dp[l][r], dp[l][k]+dp[k+1][r])
        return dp[0][n-1]

class Solution:
    def strangePrinter(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if n == 0: return 0
        dp = [[0,]*(n) for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i][i] = 1
            for j in range(i+1,n):
                dp[i][j] = dp[i+1][j]+1
                for k in range(i+1,j+1):
                    if s[i] == s[k]:
                        dp[i][j] = min(dp[i][j], dp[i+1][k-1]+dp[k][j])
        return dp[0][n-1]

class Solution:
    def strangePrinter(self, s: str) -> int:
        memo = {}
        def dp(i, j):
            if i > j: return 0
            if (i, j) not in memo:
                ans = dp(i+1, j) + 1
                for k in range(i+1, j+1):
                    if s[k] == s[i]:
                        ans = min(ans, dp(i, k-1) + dp(k+1, j))
                memo[i, j] = ans
            return memo[i, j]

        return dp(0, len(s) - 1)