#From end to begin 

"""
下面解不可以DFS, BFS 一起, 错误的
for z in q:
    for d, v in dir_.items():
        if z + d in grid:
            if grid[z+d] == v:
                q.append(z+d)
            else:
                nxt.append(z+d)
            grid.pop(z+d)

比如: 

   (0,0), (0,1)  
    ->  ^
    ^   |
    |  ->    
  (1,0)  (1,1) 


  比如 DFS (1,1) -> (0,1) -> (0,0) -> (1,0)  不需要改变方向
如果 改变 (1,0) 方向 
        (0,0) -> (1,0) nxt
        (0,0) -> (0,1) -> (0,0) q, 到了 (0,0) 发现(1,0) 已经不avaialable 错误的

"""

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        if m == n == 1:
            return 0
        dir_ = {1j**3: 1, 1j**2:3, 1j**1:2, 1j**0:4 }
        grid = {i+1j*j : val for i, row in enumerate(grid) for j, val in enumerate(row)}
        q = [n-1+1j*(m-1)]   
        grid.pop(n-1+1j*(m-1))
        step = 0
        while True:
            #DFS, Go to every possible way
            for z in q:
                for d, v in dir_.items():
                    if z + d in grid and grid[z+d] == v:
                        if z+d == 1j*0:
                            return step
                        q.append(z+d)
                        grid.pop(z+d)
            
            #BFS
            nxt = []
            for z in q:
                for d, v in dir_.items():
                    if z + d in grid and grid[z+d] != v:
                        if z+d == 1j*0:
                            return step + 1
                        nxt.append(z+d)
                        grid.pop(z+d)
            q= nxt 
            step += 1





class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        if m == n == 1:
            return 0
        dir_ = {2:1j**3, 4:1j**2, 1:1j**1, 3:1j**0 }
        grid = {i+1j*j : val for i, row in enumerate(grid) for j, val in enumerate(row)}
        q = [0]
        step = 0
        while True:
            #DFS, Go to every possible way
            for z in q:
                if z not in grid:
                    continue
                if z + dir_[grid[z]] in grid:
                    if z+ dir_[grid[z]] == (n-1) + 1j*(m-1):
                        return step
                    q.append(z + dir_[grid[z]])
                grid.pop(z)
            
            #BFS
            # print(q)
            nxt = []
            for z in q:
                for d in dir_.values():
                    if z + d in grid:
                        if z+d == (n-1) + 1j*(m-1):
                            return step + 1
                        nxt.append(z+d)
            q= nxt 
            #print('nxt',nxt)
            step += 1

class Solution:
    def minCost(self, A):
        n, m, inf, k = len(A), len(A[0]), 10**9, 0
        dp = [[inf] * m for i in range(n)]
        dirt = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        bfs = []

        def dfs(x, y):
            if not (0 <= x < n and 0 <= y < m and dp[x][y] == inf): return
            dp[x][y] = k
            bfs.append([x, y])
            dfs(x + dirt[A[x][y] - 1][0], y + dirt[A[x][y] - 1][1])

        dfs(0, 0)
        while bfs:
            k += 1
            bfs, bfs2 = [], bfs
            [dfs(x + i, y + j) for x, y in bfs2 for i, j in dirt]
        return dp[-1][-1]