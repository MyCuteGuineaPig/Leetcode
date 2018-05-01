"""
688. Knight Probability in Chessboard

"""

import collections
class Solution:
    def knightProbability(self, N, K, r, c):
        """
        :type N: int
        :type K: int
        :type r: int
        :type c: int
        :rtype: float
        """
        dp = collections.defaultdict(int)
        dp[(r,c)] = 1  
        dir = [[-2,-1],[-1,-2],[-2,1],[1,-2],[-1,2],[2,-1],[1,2],[2,1]]
        for _ in range(K):
            new = collections.defaultdict(int)
            for p, v in dp.items():
                for x_add, y_add in dir:
                    x, y = x_add+ p[0], y_add + p[1]
                    if x<0 or y<0 or x>=N or y>=N: continue
                    new[(x, y)] += 1/8*v
            dp = new
        return sum(v for v in dp.values())



import collections
class Solution:
    def knightProbability(self, N, K, r, c):
        """
        :type N: int
        :type K: int
        :type r: int
        :type c: int
        :rtype: float
        """
        dp = collections.defaultdict(lambda: -1)
        dir = [[-2,-1],[-1,-2],[-2,1],[1,-2],[-1,2],[2,-1],[1,2],[2,1]]
        def dfs(i,j, k):
            if i<0 or j<0 or i>=N or j>=N: 
                return 0
            if k == 0:
                return 1
            if dp[(i,j,k)] != -1:
                return dp[(i,j,k)]
            dp[(i,j,k)] = 0
            for x_add, y_add in dir:
                    x, y = x_add+ i, y_add + j
                    dp[(i,j,k)] += 1/8*dfs(x,y,k-1)
            return dp[(i,j,k)]
        return dfs(r,c,K)




class Solution:
    def __init__(self):
        self.mem = {}
    def knightProbability(self, N, K, r, c):

        if (r, c, K) in self.mem:
            return self.mem[(r, c, K)]
        
        if r>=2*K and r+2*K<N and c>=2*K and c+2*K<N:
            return 1
        d = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]
        
        
        ret = 0
        for (dr, dc) in d:
            nr, nc = r+dr, c+dc
            if 0<=nr<N and 0<=nc<N:
                ret += 0.125*self.knightProbability(N, K-1, nr, nc)
        
        self.mem[(r, c, K)] = ret
        self.mem[(c, r, K)] = ret
        self.mem[(N-1-r, N-1-c, K)] = ret
        self.mem[(N-1-c, N-1-r, K)] = ret
        return ret


