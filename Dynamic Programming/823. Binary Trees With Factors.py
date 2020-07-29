class Solution:
    def numFactoredBinaryTrees(self, A: List[int]) -> int:
        dp = {}
        for a in sorted(A):
            dp[a] = sum(dp[b] * dp.get(a / b, 0) for b in dp if a % b == 0) + 1
        return sum(dp.values()) % (10**9 + 7)