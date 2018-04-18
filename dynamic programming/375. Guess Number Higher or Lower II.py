"""
375. Guess Number Higher or Lower II
"""

class Solution:
    def getMoneyAmount(self,n):
        """
        :type n: int
        :rtype: int
        """
        dp = [[float('inf') for _ in range(n+1)] for _ in range(n+1)]
        for i in range(1,n+1):
            dp[i][i] = 0
            for j in range(i,0,-1):
                for k in range(j+1,i):
                    dp[j][i] = min(dp[j][i],k+max(dp[j][k-1],dp[k+1][i]))
                if i-j == 1:
                    dp[j][i] = j
        return dp[1][n]


class Solution:
    def getMoneyAmount(self,n):
        """
        :type n: int
        :rtype: int
        """
        dp = [[0]*(n+1) for _ in range(n+1)]
        for i in range(1,n+1):
            for j in range(i-1,0,-1):
                dp[j][i] = min((k+max(dp[j][k-1],dp[k+1][i]) for k in range(j+1,i)),default=j)
        return dp[1][n]


class Solution:
    def getMoneyAmount(self, n):
        """
        :type n: int
        :rtype: int
        """
        need = [[0] * (n + 1) for _ in range(n + 1)]
        for lo in range(n, 0, -1):
            for hi in range(lo+1, n+1):
                need[lo][hi] = min(x + max(need[lo][x-1], need[x+1][hi]) for x in range(lo,hi))
        return need[1][n]


"""
Top-down with memoization, subclassing dict for convenience. Simpler than bottom-up because I don’t need to specify ranges/loops 
for lo and hi and don’t need to think about their orders and how big my DP matrix needs to be. On the other hand, it’s slower.
"""

def getMoneyAmount(self, n):
    class Need(dict):
        def __missing__(self, (lo, hi)):
            if lo >= hi:
                return 0
            ret = self[lo, hi] = min(x + max(self[lo, x-1], self[x+1, hi])
                                     for x in range(lo, hi))
            return ret
    return Need()[1, n]