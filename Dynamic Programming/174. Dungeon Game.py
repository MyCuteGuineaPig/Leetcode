class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        dp = [[0 for _ in range(n+1) ] for _ in range(m+1)]
        for i in range(m):
            dp[i][n] = float('inf')
        for j in range(n):
            dp[m][j] = float('inf')
        dp[m][n-1] = dp[m-1][n] = 1
        
        for i in range(m-1,-1,-1):
            for j in range(n-1,-1,-1):
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])
        return dp[0][0]



class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        dp = [float('inf') for _ in range(n+1) ]
        dp[n] = dp[n-1] = 1
        for i in range(m-1,-1,-1):
            if i != m-1:
                dp[n] = float('inf')
            for j in range(n-1,-1,-1):
                dp[j] = max(1, min(dp[j], dp[j+1]) - dungeon[i][j])
        return dp[0]
    
class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        n = len(dungeon[0])
        need = [2**31] * (n-1) + [1]
        for row in dungeon[::-1]:
            for j in range(n)[::-1]:
                need[j] = max(min(need[j:j+2]) - row[j], 1)
        return need[0]
    