class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3
        def linear(arr):
            eat = collections.deque([[0] + [-math.inf]*n] * 2) #加0怕有边界问题 因为 i - 1
            res = 0
            for x in arr:
                eat += [i and max(eat[-1][i], eat[-2][i-1]+x) for i in range(n+1)], #1 and 5, return 5
                eat.popleft()
                res = max(res, eat[-1][n])
            return res
        return max(linear(slices[1:]), linear(slices[:-1]))


class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3 
        def dp(arr):
            eat = collections.deque([[0,]*n]*2)
            for i, x  in enumerate(arr):
                eat += [ i >= 2*j and max(eat[-1][j], eat[-2][j-1] + x) for j in range(n)],
                eat.popleft()
            return eat[-1][-1]
        return max(dp(slices[:-1]), dp(slices[1:]))


class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3 
        def dp(arr):
            eat = [[0,]*len(arr) for _ in range(2)]
            for i in range(n):
                for j, x in enumerate(arr):
                    if j >= 2*i:
                        eat[i%2][j] = max(eat[i%2][j-1], eat[(i-1)%2][j-2] + x)
            return eat[len(arr)%2][-1]
        return max(dp(slices[:-1]), dp(slices[1:]))