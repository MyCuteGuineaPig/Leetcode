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
