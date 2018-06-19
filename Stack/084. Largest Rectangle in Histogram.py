"""
84. Largest Rectangle in Histogram


Input: [2,1,5,6,2,3]
Output: 10
"""


class Solution:
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        stk, n, res = [], len(heights), 0
        if n == 1: return heights[0]
        for i in range(n+1):
            while stk and ( i == n or heights[stk[-1]] > heights[i]):
                tall = heights[stk.pop()]
                x = i-stk[-1]-1 if stk else i
                res = max(res, tall*x)
            stk.append(i)
        return res