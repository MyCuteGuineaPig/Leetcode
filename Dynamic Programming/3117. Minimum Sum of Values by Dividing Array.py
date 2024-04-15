class Solution:
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:
        n = len(nums)
        k = len(andValues)

        @functools.cache
        def cal(mask, i, j):
            if i == n and j == k:
                return 0
            if i == n or j == k:
                return inf
            mask &= nums[i]
            if mask < andValues[j]: return inf
            if mask == andValues[j]:
                return min(cal((1<<32) - 1, i+1, j+1) + nums[i], cal(mask, i+1, j))
            return cal(mask, i+1, j)

        ans = cal((1<<32) -1, 0, 0)
        return -1 if ans >= inf else ans