class Solution:
    def numDistinctIslands(self, grid):
        islands = set([])
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 1:
                    islands.add(self.dfs(grid, i, j, "s"))

        return len(islands)

    def dfs(self, g, i, j, path):
        if i < 0 or j < 0 or i >= len(g) or j >= len(g[i]) or g[i][j] == 0:
            return ""

        g[i][j] = 0
        return path \
               + self.dfs(g, i+1, j, "d") + "u" \
               + self.dfs(g, i-1, j, "u") + "d" \
               + self.dfs(g, i, j+1, "r") + "l" \
               + self.dfs(g, i, j-1, "l") + "r"


class Solution(object):
    def numDistinctIslands(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        island_shapes = set()
        rows, cols = len(grid), len(grid[0])
        def dfs(i, j, positions, rel_pos):
            grid[i][j] = -1
            for direction in ((0, 1), (1, 0), (-1, 0), (0, -1)):
                next_i, next_j = i + direction[0], j + direction[1]
                if (0 <= next_i < rows and 0 <= next_j < cols) and grid[next_i][next_j] == 1:
                    new_rel_pos = (rel_pos[0] + direction[0], rel_pos[1] + direction[1])
                    positions.append(new_rel_pos)
                    dfs(next_i, next_j, positions, new_rel_pos)
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 1:
                    positions = []
                    dfs(i, j, positions, (0, 0))
                    island_shapes.add(tuple(positions))
        return len(island_shapes)