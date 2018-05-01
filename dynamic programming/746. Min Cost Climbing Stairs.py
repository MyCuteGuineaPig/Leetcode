"""
746. Min Cost Climbing Stairs
"""
class Solution:
    def minCostClimbingStairs(self, cost):
        """
        :type cost: List[int]
        :rtype: int
        """
        take, skip = cost[1], cost[0]
        for i in cost[2:]:
            take, skip = min(skip, take)+i, take
        return min(take,skip)
        