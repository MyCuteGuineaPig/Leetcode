
class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        n = len(piles)
        dp = [[0] * n for i in range(n)]
        for i in range(n): dp[i][i] = piles[i]
        for d in range(1, n):
            for i in range(n - d):
                dp[i][i + d] = max(piles[i] - dp[i + 1][i + d], piles[i + d] - dp[i][i + d - 1])
        return dp[0][-1] > 0

# O(n) space
class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        n = len(piles)
        dp = piles[:]
        for d in range(1, n):
            for i in range(n - d):
                dp[i] = max(piles[i] - dp[i + 1], piles[i + d] - dp[i])
        return dp[0] > 0

class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        cache = {}
        piles = tuple(piles)
        def firstscore(i,j):
            if i>=j: return 0
            if j==i+1 and j < len(piles): return piles[i]
            if (i,j) in cache: return cache[i,j]
            res = max(piles[i]+min(firstscore(i+2,j), firstscore(i+1,j-1)) , piles[j-1] + min(firstscore(i+1,j-1), firstscore(i,j-2)))
            cache[i,j] = res
            return res

        Alex = firstscore(0,len(piles))
        Lee = sum(piles) - Alex
        return Alex > Lee