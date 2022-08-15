import numpy as np
class Solution:
    def largestLocal(self, grid: List[List[int]]) -> List[List[int]]:
        grid = np.array(grid)
        return [[ np.max(grid[i:i+3,j: j+3]) for j in range(len(grid)-2)] for i in range(len(grid)-2)]