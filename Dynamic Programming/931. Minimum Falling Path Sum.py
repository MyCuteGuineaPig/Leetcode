class Solution:
    def minFallingPathSum(self, A: List[List[int]]) -> int:
        dp = A[0]
        for row in A[1:]:
            dp = [value + min([dp[c], dp[max(c - 1, 0)], dp[min(len(A) - 1, c + 1)]]) for c, value in enumerate(row)]
        return min(dp)

class Solution:
    def minFallingPathSum(self, A):
        for i in range(1, len(A)):
            for j in range(len(A)):
                A[i][j] += min(A[i - 1][j and j - 1:j + 2])
        return min(A[-1])