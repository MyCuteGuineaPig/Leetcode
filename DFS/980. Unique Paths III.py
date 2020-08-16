class Solution:
    def uniquePathsIII(self, grid: List[List[int]]) -> int:
        self.res = 0
        m, n, empty = len(grid), len(grid[0]), 1
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    x, y = (i, j)
                elif grid[i][j] == 0:
                    empty += 1

        def dfs(x, y, empty):
            if not (0 <= x < m and 0 <= y < n and grid[x][y] >= 0): return
            if grid[x][y] == 2:
                self.res += empty == 0
                return
            grid[x][y] = -2
            dfs(x + 1, y, empty - 1)
            dfs(x - 1, y, empty - 1)
            dfs(x, y + 1, empty - 1)
            dfs(x, y - 1, empty - 1)
            grid[x][y] = 0
        dfs(x, y, empty)
        return self.res


class Solution:
    def uniquePathsIII(self, grid):
        n,m = len(grid), len(grid[0])
        start = 0
        final = 0
        fi = fj = 0
        # 先获得起始位置和终点位置，以及起始和终点的位表示
        for i in range(n):
            for j in range(m):
                if grid[i][j] != -1:
                    final += 1 << (i*m+j)
                if grid[i][j] == 1:
                    start += 1 << (i*m+j)
                    si, sj = i, j
                if grid[i][j] == 2:
                    fi, fj = i, j

        # 使用记忆化思想，存储已经走过的情况
        cache = {(start,si,sj): 1}
        def solve(status, i, j):
            if (status,i,j) in cache: return cache[status,i,j]
            res = 0
            now_status = 1 << (i*m + j)
            # 每次向四个临近结点移动，但要保证临近结点能走
            for x,y in [(i+1,j), (i-1,j), (i,j+1), (i,j-1)]:
                if 0<=x<n and 0<=y<m and grid[x][y] != -1:
                    # 保证每个空白位置只走一遍
                    mask = 1 << (x*m+y)
                    if status & mask:
                        res += solve(status ^ now_status, x, y)
            cache[status,i,j] = res
            return res
        return solve(final, fi, fj)