"""
576. Out of Boundary Paths
"""

# DP
class Solution:
    def findPaths(self, m: int, n: int, N: int, i: int, j: int) -> int:
        M = 10**9 + 7
        dp = collections.defaultdict(int)
        dp[(i,j)] = 1
        res = 0;
        dir_ = [[-1,0],[0,-1],[1,0],[0,1]]
        for _ in range(0,N):
            newdp = collections.defaultdict(int)
            for i, v in dp.items():
                for x_add, y_add in dir_:
                    x = i[0] + x_add
                    y = i[1] + y_add
                    if x<0 or y<0 or x>=m or y>=n:
                        res = (res + v) % M
                    else:
                        newdp[(x,y)] += dp[i]
            dp = newdp
        return res

# DP
class Solution:
    def findPaths(self, R: int, C: int, N: int, sr: int, sc: int) -> int:
        MOD = 10**9 + 7
        nxt = [[0] * C for _ in range(R)]
        nxt[sr][sc] = 1

        ans = 0
        for time in range(N):
            cur = nxt
            nxt = [[0] * C for _ in range(R)]
            for r, row in enumerate(cur):
                for c, val in enumerate(row):
                    for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                        if 0 <= nr < R and 0 <= nc < C:
                            nxt[nr][nc] += val
                            nxt[nr][nc] %= MOD
                        else:
                            ans += val
                            ans %= MOD
        return ans



# DP
class Solution:
    def findPaths(self, m: int, n: int, N: int, i: int, j: int) -> int:
        M = [[0 for _ in range(n)] for _ in range(m)]
        for _ in range(N):
            M = [[(x == 0 or M[x - 1][y]) + (x + 1 == m or M[x + 1][y])
                  + (y == 0 or M[x][y - 1]) + (y + 1 == n or M[x][y + 1])
                  for y in range(n)] for x in range(m)]
        return M[i][j] % (10 ** 9 + 7)

# DFS
import collections
class Solution:
    def findPaths(self, m, n, N, i, j):
        """
        :type m: int
        :type n: int
        :type N: int
        :type i: int
        :type j: int
        :rtype: int
        """
        M = 10**9 + 7
        dp = collections.defaultdict(lambda: -1)
        def dfs(i, j, k):
            if k<0:
                return 0
            if i<0 or j<0 or i>=m or j>=n:
                return 1
            if dp[(i,j,k)]!=-1: 
                return dp[(i,j,k)]
            dp[(i,j,k)] = (dfs(i-1,j,k-1) + dfs(i,j-1,k-1) + dfs(i+1,j,k-1) +dfs(i,j+1,k-1))%M
            return dp[(i,j,k)]
        
        return dfs(i,j,N)



        
           
import numpy as np

class Solution(object):
    def findPaths(self, m, n, N, i, j):
        paths = np.zeros((m, n), dtype=np.int64)
        paths[i][j] = 1
        out = 0
        mod = 10**9 + 7
        for _ in range(N):
            prev = paths % mod
            paths = np.zeros((m, n), dtype=np.int64)
            paths[1:] += prev[:-1]
            paths[:-1] += prev[1:]
            paths[:,1:] += prev[:,:-1]
            paths[:,:-1] += prev[:,1:]
            out += 4 * prev.sum() - paths.sum()
        return int(out % mod)

"""
parity 相当于每次进出的位子，
每次进入在只能是 i+j 除以2 余1 进入（i+j）%2 = 0
或者  （i+j）%2 = 0 进入（i+j）%2 = 1

"""
class Solution:
    def findPaths(self, m, n, N, i, j):
        """
        :type m: int
        :type n: int
        :type N: int
        :type i: int
        :type j: int
        :rtype: int
        """
        cnt = 0
        if m == 0 or n == 0:
            return 0
        dp = [[0,]*(n + 2) for _ in range(m + 2)]
        parity = (i + j) % 2
        dp[i+1][j+1] = 1
        for _ in range(N):
            for row in range(1, m+1):
                for col in range(1, n+1):
                    if (row + col) % 2 != parity:
                        dp[row][col] = dp[row+1][col] + \
                                       dp[row-1][col] + \
                                       dp[row][col+1] + \
                                       dp[row][col-1]
            for row in range(1, m+1):
                if (row + 1) % 2 == parity:
                    cnt += dp[row][1]
                if (row + n) % 2 == parity:
                    cnt += dp[row][n]               
            for col in range(1, n+1):
                if (col + 1) % 2 == parity:
                    cnt += dp[1][col]
                if (col + m) % 2 == parity:
                    cnt += dp[m][col]
            parity = (parity + 1) % 2
        return cnt % (10**9+7)
        