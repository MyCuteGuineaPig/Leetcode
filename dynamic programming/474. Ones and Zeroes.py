"""
474. Ones and Zeroes
"""

class Solution:
    def findMaxForm(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]
        for s in strs:
            c0 = s.count('0')
            c1 = s.count('1')
            for i in range(m, c0-1,-1):
                for j in range(n,c1-1,-1):
                    dp[i][j] = max(dp[i-c0][j-c1]+1, dp[i][j])
        return dp[-1][-1]