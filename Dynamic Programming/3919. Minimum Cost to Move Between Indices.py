class Solution:
    def minCost(self, nums: list[int], queries: list[list[int]]) -> list[int]:
        n = len(nums)
        left_cost = [0]*n
        right_cost = [0]*n

        for i in range(n-1):
            if i == 0 or nums[i+1]-nums[i] <  nums[i] - nums[i-1]:
                left_cost[i+1] = left_cost[i] + 1 
            else:
                left_cost[i+1] = left_cost[i] + nums[i+1] - nums[i]

        for i in range(n-1, 0, -1):
            if i == n-1 or nums[i] - nums[i-1] <= nums[i+1] - nums[i]: # if equal, choose the smaller index.
                right_cost[i-1] = right_cost[i] + 1 
            else:
                right_cost[i-1] = right_cost[i] + nums[i] - nums[i-1]

        res = []
        for l, r in queries:
            if l < r: 
                res.append(left_cost[r] - left_cost[l])
            else:
                res.append(right_cost[r] - right_cost[l])

        return res