"""
63. Unique Paths II
"""

class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid):
        if len(obstacleGrid) == 0 or obstacleGrid[0][0] == 1:
             return 0
        n, m = len(obstacleGrid), len(obstacleGrid[0])
        if obstacleGrid[n-1][m-1] == 1 : return 0
        table = [0]*m
        for i, x in enumerate(obstacleGrid):
            for j, y in enumerate(x):
                table[j] = (table[j] if y!=1 and i>0 else 0) + (table[j-1] if y!= 1 and j>0 else 0) + (1 if i == 0 and j == 0 else 0)
        return table[m-1]
        