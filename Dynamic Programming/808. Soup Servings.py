"""

f(a - 4, b) 表示serve A 100 ml, serve B 0 ml
f(a - 3, b - 1) 表示serve A 25 ml, serve B 75 ml
f(a - 2, b - 2) 表示serve A 50 ml, serve B 50 ml
f(a - 1, b - 3) 表示serve A 25 ml, serve B 75 ml


"""
class Solution:
    memo = {}
    def soupServings(self, N: int) -> float:
        
        if N > 4800: return 1
        def f(a, b):
            if (a, b) in self.memo: return self.memo[(a, b)]
            if a <= 0 and b <= 0: return 0.5
            if a <= 0: return 1
            if b <= 0: return 0 
            self.memo[(a, b)] = 0.25 * (f(a - 4, b) + f(a - 3, b - 1) + f(a - 2, b - 2) + f(a - 1, b - 3))
            return self.memo[(a, b)]
        N = math.ceil(N / 25.0)
        return f(N, N)


class Solution:
    memo = {}
    def soupServings(self, N: int) -> float:
        
        visited = {}
        def dfs(a, b):
            if (a, b) in visited: return visited[(a, b)]
            elif a <= 0 or b <= 0: return (a < b and 1) or (a == b and 0.5) or (b < a and 0)
            visited[(a, b)] = 0.25 * (dfs(a - 100, b) + dfs(a - 75, b - 25) + dfs(a - 50, b -50) + dfs(a - 25, b - 75))
            return visited[(a, b)] 
        return N > 4800 and 1 or round(dfs(N, N), 5)


# Bottom-up 
class Solution:
    memo = {}
    def soupServings(self, N: int) -> float:
        
        N = N//25 + (N % 25 > 0) #or N = (N+24)//25
        if N >= 500:
            return 1
        dp = [[0]*(N+1) for _ in range(N+1)]
        operations = [(4, 0), (3, 1), (2, 2), (1, 3)]
        dp[-1][-1] = 1
        
        for i in range(N, 0, -1):
            for j in range(N, 0, -1):
                for a, b in operations:
                    if i-a < 0 and j-b < 0:
                        dp[0][0] += dp[i][j]*0.25
                    elif i-a < 0:
                        dp[0][j-b] += dp[i][j]*0.25
                    elif j-b < 0:
                        dp[i-a][0] += dp[i][j]*0.25
                    else:
                        dp[i-a][j-b] += dp[i][j]*0.25    
        a_total = 0
        for i in range(N+1):
            a_total += dp[0][i]
        
        return a_total - dp[0][0] / 2
        
