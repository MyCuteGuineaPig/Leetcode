class Solution:
    def maxNonDecreasingLength(self, A: List[int], B: List[int]) -> int:
        res = dp1 = dp2 = 1
        for i in range(1, len(A)):
            t11 = dp1 + 1 if A[i - 1] <= A[i] else 1
            t12 = dp1 + 1 if A[i - 1] <= B[i] else 1
            t21 = dp2 + 1 if B[i - 1] <= A[i] else 1
            t22 = dp2 + 1 if B[i - 1] <= B[i] else 1
            dp1 = max(t11, t21)
            dp2 = max(t12, t22)
            res = max(res, dp1, dp2)
        return res