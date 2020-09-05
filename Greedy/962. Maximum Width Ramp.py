"""
O(N)
"""
class Solution:
    def maxWidthRamp(self, A: List[int]) -> int:
        s = []
        res = 0
        for i, a in enumerate(A):
            if not s or A[s[-1]] > a:
                s.append(i)
        for j in range(len(A))[::-1]:
            while s and A[s[-1]] <= A[j]:
                res = max(res, j - s.pop())
        return res


"""
O(NlogN)
"""
class Solution:
    def maxWidthRamp(self, A: List[int]) -> int:
        stack = []
        res = 0
        for i in range(len(A))[::-1]:
            if not stack or A[i] > stack[-1][0]:
                stack.append([A[i], i])
            else:
                j = stack[bisect.bisect(stack, [A[i], i])][1]
                res = max(res, j - i)
        return res


class Solution:
    def maxWidthRamp(self, A: List[int]) -> int:
        ind, mx, index = float("inf"), 0, collections.defaultdict(list)
        for i, num in enumerate(A):
            index[num].append(i)
        for num in sorted(A):
            mx = max(mx, index[num][-1] - ind)
            ind = min(ind, index[num][0])
        return mx
