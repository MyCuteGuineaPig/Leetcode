""""
629. K Inverse Pairs Array
"""

class Solution:
    def kInversePairs(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        M = 10**9 + 7
        if n<=0 or k>n*(n-1)/2 : return 0;
        dp = [[0,]*(k+1) for _ in range(n+1)]; dp[0][0] = 1
        for i in range(1,n+1):
            dp[i][0] = 1
            for j in range(1,k+1):
                dp[i][j] = (dp[i-1][j] + dp[i][j-1] - (dp[i-1][j-i] if j>=i else 0)) % M
        #print(dp)
        return dp[-1][-1]

class Solution:
    def kInversePairs(self, n: int, k: int) -> int:
        dp = [1] + [0] * k
        for i in range(2, n + 1):
            for j in range(1, k + 1): dp[j] += dp[j - 1]
            for j in range(k, 0, -1): dp[j] -= j - i >= 0 and dp[j - i]
        return dp[k] % (10**9 + 7)