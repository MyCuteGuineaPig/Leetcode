class Solution:
    def maxSubarraySumCircular(self, A: List[int]) -> int:
        total, maxSum, curMax, minSum, curMin = 0, A[0], 0, A[0], 0
        for a in A:
            curMax = max(curMax + a, a)
            maxSum = max(maxSum, curMax)
            curMin = min(curMin + a, a)
            minSum = min(minSum, curMin)
            total += a
        return max(maxSum, total - minSum) if maxSum > 0 else maxSum

class Solution:
    def maxSubarraySumCircular(self, A: List[int]) -> int:
        if max(A) <= 0: return max(A)
        endmax = [i for i in A]
        endmin = [i for i in A]
        for i in range(1,len(A)):
            if endmax[i-1] > 0: endmax[i] += endmax[i-1]
            if endmin[i-1] < 0: endmin[i] += endmin[i-1]

        return max(max(endmax),sum(A) - min(endmin))