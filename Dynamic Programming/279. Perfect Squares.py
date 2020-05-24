"""
279. Perfect Squares
"""

#bottom-up
class Solution(object):
    _num = [0]
    def numSquares(self, n):
        """
        :type n: int
        :rtype: int
        """
        num = self._num
        while len(num) <= n:
            num += min(num[-i*i] for i in range(1, int(len(num)**0.5+1))) + 1,
        return num[n]


#bottom-up
class Solution:
    def numSquares(self, n: int) -> int:
        dp = [n+1 for _ in range(n)]
        i = 1
        while i*i <= n:
            dp[i*i-1] = 1
            j = 1 
            for j in range(i*i+1, n+1):
                dp[j-1]= min(dp[j-1], dp[j-i*i-1]+1)
            i+=1
        return dp[-1]


#top-down
class Solution:
    def numSquares(self, n: int) -> int:
        dp = [-1 for i in range(n+1)]
        dp[0] = 0
        def topDown(i):
            if i < 0: 
                return n
            if dp[i] >= 0:
                return dp[i]
            j = 1
            cur = i+1
            while j*j <= i:
                cur = min(cur, topDown(i-j*j)+1)
                j+=1
            dp[i] = cur
            return dp[i]
        return topDown(n)


#Static DP
class Solution:
    def __init__(self,):
        self.dp = [0,1]
        self.start = 1
    
    def numSquares(self, n: int) -> int:
        if n <= self.start:
            return self.dp[n]
        self.dp += [0 for _ in range(n - self.start)]
        for i in range(self.start + 1, n+1):
            cur = i
            j = 1
            while j*j <= n and i - j*j >= 0:
                cur = min(cur, 1 + self.dp[i - j*j])
                j += 1
            self.dp[i] = cur
        self.start = n
        return self.dp[n]

# BFS

class Solution:
    def numSquares(self, n: int) -> int:
        q = collections.deque()
        square = []
        i = 0
        while i*i <= n:
            square += i*i,
            q.append(i*i)
            i+=1
        if square[-1] == n:
            return 1
        dp = {}
        dp[0] = 1
        step = 1
        while q:
            size = len(q)
            step += 1
            for _ in range(size):
                cur = q.popleft()
                for i in square:
                    if cur + i == n:
                        return step
                    if i + cur > n:
                        break
                    if i + cur < n and i + cur not in dp:
                        dp[i+cur] = step
                        q.append(i+cur)

# Static DP
class Solution:
    _dp = [0]
    def numSquares(self, n: int) -> int:
        dp = self._dp
        while len(dp) <= n:
            dp += min(dp[-i*i] for i in range(1, int(len(dp)**0.5+1))) + 1,
        return dp[n]