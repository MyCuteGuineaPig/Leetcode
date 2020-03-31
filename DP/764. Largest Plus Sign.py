"""
764. Largest Plus Sign
"""
class Solution:
    def orderOfLargestPlusSign(self, N, mines):
        """
        :type N: int
        :type mines: List[List[int]]
        :rtype: int
        """
        dp = [[N,]*N for _ in range(N)]
        for i,j in mines:
            dp[i][j] = 0
        for i in range(N):
            u, d , l, r = 0 , 0, 0, 0
            j, k = 0, N-1
            while j<=N-1 :
                l = (l + 1) if dp[i][j] != 0 else 0
                r = (r + 1) if dp[i][k] != 0 else 0
                u = (u + 1) if dp[j][i] != 0 else 0
                d = (d + 1) if dp[k][i] != 0 else 0
                
                dp[i][j] = min(dp[i][j], l)
                dp[i][k] = min(dp[i][k], r)
                dp[j][i] = min(dp[j][i], u)
                dp[k][i] = min(dp[k][i], d)
                
                
                j+=1
                k-=1
        return max(v for i in dp for v in i)