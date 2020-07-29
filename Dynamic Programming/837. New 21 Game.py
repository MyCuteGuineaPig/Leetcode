class Solution:
    def new21Game(self, N: int, K: int, W: int) -> float:
        if K == 0 or N >= K + W: return 1
        dp = [1.0] + [0.0] * N
        Wsum = 1.0
        for i in range(1, N + 1):
            dp[i] = Wsum / W
            if i < K: Wsum += dp[i]
            if i - W >= 0: Wsum -= dp[i - W]
        return sum(dp[K:])


"""
F(x) = (F(x+1) + F(x+2) + ... + F(x+W)) / W
F(x+1) = (F(x+2) + F(x+3) + ... + F(x+1+W)) / W

After a substraction, we have

F(x) = F(x+1) - 1/W * (F(x+1+W) - F(x+1))

"""

class Solution:
    def new21Game(self, N: int, K: int, W: int) -> float:
        return self.dfs(N, K, W, 0, {})
    
    def dfs(self, N, K, W, cur, memo):
        
        if cur == K-1:
            return min(N-K+1, W) / W
        if cur > N:
            return 0
        elif cur >= K:
            return 1.0
        
        if cur in memo:
            return memo[cur]
        
        prob = self.dfs(N, K, W, cur+1, memo) - (self.dfs(N, K, W, cur+1+W, memo) - self.dfs(N, K, W, cur+1, memo)) / W
        
        memo[cur] = prob
        
        return prob