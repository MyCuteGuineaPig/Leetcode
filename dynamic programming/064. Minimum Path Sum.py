"""
64. Minimum Path Sum
"""
class Solution:
    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if len(grid) == 0: return 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if i!=0 or j!=0:    
                    grid[i][j] += grid[i][j-1] if i == 0 else 0 +grid[i-1][j] if j== 0 else 0 +  min(grid[i][j-1], grid[i-1][j]) if i > 0 and j> 0 else 0 
        return grid[-1][-1]