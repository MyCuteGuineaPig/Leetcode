"""
85. Maximal Rectangle

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]

"""
class Solution:
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix or not matrix[0]: return 0
        def cal_area():
            stk, res = [], 0
            for i in range(len(heights)+1):
                while stk and (i == len(heights) or heights[stk[-1]] > heights[i]):
                    h = heights[stk.pop()]
                    x = i - stk[-1] -1 if stk else i
                    res = max(res, x*h)
                stk.append(i)
            #print(heights,res)
            return res
        n, m, res = len(matrix), len(matrix[0]), 0
        heights = [0]*m
        for i in range(n):
            for j in range(m):
                heights[j] = heights[j] + 1 if matrix[i][j] == '1' else 0
            res = max(res, cal_area())
        return res



            
    