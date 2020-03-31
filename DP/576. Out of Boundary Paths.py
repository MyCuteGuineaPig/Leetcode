"""
576. Out of Boundary Paths
"""


"""
dp with memoization get time out (TLE)
"""
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
        dp = collections.defaultdict(int) #不能设置默认为0， 否则可能有0的情况无法返回
        def dfs(i, j, k):
            if k<0:
                return 0
            if i<0 or j<0 or i>=m or j>=n:
                return 1
            if dp[(i,j,k)]>0: 
                return dp[(i,j,k)]
            dp[(i,j,k)] = (dfs(i-1,j,k-1) + dfs(i,j-1,k-1) + dfs(i+1,j,k-1) +dfs(i,j+1,k-1))%M
            return dp[(i,j,k)]
        
        return dfs(i,j,N)

"""
Accepted
"""

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


"""
Accepted
"""

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
        