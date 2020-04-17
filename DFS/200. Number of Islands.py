class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid or not grid[0]:
            return 0
        m, n = len(grid), len(grid[0])
        grid = {i+j*1j:1 for i in range(m) for j in range(n) if grid[i][j] == '1' }
        print(grid)
        def dfs(i):
            if i not in grid:
                return 0
            grid.pop(i)
            for k in range(4):
                dfs(i + 1j**k)
            return 1
        return sum(dfs(i+j*1j) for i in range(m) for j in range(n))

    
 """
  grid.pop(z,0) 如果有z, pop dictionary value, 否则pop 0
  
  z + 1j**k for k in range(4): z的四个方向
  
  比如 z = 1+4j
  
  1+4j + 1j**0 = 2 + 4j
  1+4j + 1j**1 = 1 + 5j
  1+4j + 1j**2 = 0 + 4j
  1+4j + 1j**3 = 1 + 3j
  
  
 """
