class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        row, col = len(grid), len(grid[0])
        rotting = {(i, j) for i in range(row) for j in range(col) if grid[i][j] == 2}
        fresh = {(i, j) for i in range(row) for j in range(col) if grid[i][j] == 1}
        timer = 0
        while fresh:
            if not rotting: return -1
            rotting = {(i+di, j+dj) for i, j in rotting for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)] if (i+di, j+dj) in fresh}
            fresh -= rotting
            timer += 1
        return timer


class Solution:
    def orangesRotting(self, grid):
        m, n, queue, fresh = len(grid), len(grid[0]), deque(), 0
        for i,j in product(range(m), range(n)):
            if grid[i][j] == 2: queue.append((i,j))
            if grid[i][j] == 1: fresh += 1
        dirs = [[1,0],[-1,0],[0,1],[0,-1]]
        levels = 0
        
        while queue:
            levels += 1
            for _ in range(len(queue)):
                x, y = queue.popleft()
                for dx, dy in dirs:
                    if 0<=x+dx<m and 0<=y+dy<n and grid[x+dx][y+dy] == 1:
                        fresh -= 1
                        grid[x+dx][y+dy] = 2
                        queue.append((x+dx, y+dy))
                        
        return -1 if fresh != 0 else max(levels-1, 0)


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        visit, curr = set(), deque()
		# find all fresh and rotten oranges
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    visit.add((i, j))
                elif grid[i][j] == 2:
                    curr.append((i, j))
        result = 0
        while visit and curr:
			# BFS iteration
            for _ in range(len(curr)):
                i, j = curr.popleft()  # obtain recent rotten orange
                for coord in ((i-1, j), (i+1, j), (i, j-1), (i, j+1)):
                    if coord in visit:  # check if adjacent orange is fresh
                        visit.remove(coord)
                        curr.append(coord)
            result += 1
		# check if fresh oranges remain and return accordingly
        return -1 if visit else result