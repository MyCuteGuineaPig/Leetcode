class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        d = collections.defaultdict(set)
        m = collections.defaultdict(set)
        d[1] = 2
        d[2] = 1
        d[3] = 3
        d[4] = 4
        d[5] = 5
        d[6] = 6
        m[1] = [[0,-1],[0,1]]
        m[2] = [[-1,0],[1,0]]
        m[3] = [[-1,0],[1,0]]
        m[4] = [[1,0],[0,1]]
        m[5] = [[-1,0],[0,-1]]
        m[6] = [[-1,0],[0,1]]
        def f(i, j):
            if i == len(grid) - 1 and j == len(grid[0]) - 1:
                return True
            v, grid[i][j]  = grid[i][j], grid[i][j]*-1
            for x, y in m[v]:
                ni, nj = i + x, y+j
                if ni <0 or nj < 0 or ni > len(grid)-1 or nj > len(grid[0])-1 or grid[ni][nj]<0 or grid[ni][nj] == d[v]:
                    continue 
                if f(ni,nj):
                    return True
            grid[i][j] *= -1
            return False 
        return f(0,0)

"""
Why (-d[0], -d[1]) in directions[grid[ni][nj]]:?

When traversing from one cell to the next. the next cell must have a direction that is the opposite of the direction 
we are moving in for the cells to be connected. For example, if we are moving one unit to the right, 
then from the next cell it must be possible to go one unit to the left, otherwise it's not actually connected.

"""

class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        if not grid:
            return true
        directions = {1: [(0,-1),(0,1)],
                      2: [(-1,0),(1,0)],
                      3: [(0,-1),(1,0)],
                      4: [(0,1),(1,0)],
                      5: [(0,-1),(-1,0)],
                      6: [(0,1),(-1,0)]}
        visited = set()
        goal = (len(grid)-1, len(grid[0]) - 1)
        def dfs(i, j):
            visited.add((i,j))
            if (i,j) == goal:
                return True
            for d in directions[grid[i][j]]:
                ni, nj = i+d[0], j+d[1]
                if 0 <= ni < len(grid) and 0 <= nj < len(grid[0]) and (ni, nj) not in visited and (-d[0], -d[1]) in directions[grid[ni][nj]]:
                    if dfs(ni, nj):
                        return True
            return False
        return dfs(0,0)


class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        M = len(grid)
        N = len(grid[0])

        D = []
        D.append(None) 
        D.append({2: 2, 4: 4}) #2 往左走, 4往右走， 
        # 2->2 从右侧的来只能向左， 4->4 从左侧来的，继续向右走
        D.append({1: 1, 3: 3}) #1 往下走，3往上走, 
        # 1->1 从上面来的，只能往下走, 3->3 从下面来的只能往上走
        D.append({4: 1, 3: 2})
        D.append({3: 4, 2: 1})
        D.append({4: 3, 1: 2})
        D.append({1: 4, 2: 3})

        S = []
        S.append(None)
        S.append({2: (0, -1), 4: (0, 1)})
        S.append({1: (1, 0), 3: (-1, 0)})
        S.append({4: (1, 0), 3: (0, -1)})
        S.append({3: (0, 1), 2: (1, 0)})
        S.append({4: (-1, 0), 1: (0, -1)})
        S.append({1: (0, 1), 2: (-1, 0)})

        def helper(from_direction):
            visited = []
            for _ in range(M):
                visited.append([False] * N)

            i = 0
            j = 0
            while True:
                if i < 0 or i >= M or j < 0 or j >= N: return False
                if i == M - 1 and j == N - 1: return True
                if visited[i][j]: return False

                visited[i][j] = True

                index = grid[i][j]

                if from_direction not in D[index]: return False
                i += S[index][from_direction][0]
                j += S[index][from_direction][1]
                from_direction = D[index][from_direction]

        index = grid[0][0]
        for from_direction in D[index].keys():
            if helper(from_direction):
                return True
        return False

"""
Union Find 
The center of A[0][0] has coordinates [0, 0]
The center of A[i][j] has coordinates [2i, 2j]
The top edge of A[i][j] has coordinates [2i-1, 2j]
The left edge of A[i][j] has coordinates [2i, 2j-1]
The bottom edge of A[i][j] has coordinates [2i+1, 2j]
The right edge of A[i][j] has coordinates [2i, 2j+1]

Then we apply Union Find:
if A[i][j] in [2, 5, 6]: connect center and top
if A[i][j] in [1, 3, 5]: connect center and left
if A[i][j] in [2, 3, 4]: connect center and bottom
if A[i][j] in [1, 4, 6]: connect center and right

Time O(MN) * O(UF)
Space O(MN)

"""


class Solution:
    def hasValidPath(self, A):
            m, n = len(A), len(A[0])
        uf = {(i, j): (i, j) for i in xrange(-1, m * 2) for j in xrange(-1, n * 2)}

        def find(x):
            if uf[x] != x:
                uf[x] = find(uf[x])
            return uf[x]

        def merge(i, j, di, dj):
            uf[find((i, j))] = find((i + di, j + dj))

        for i in xrange(m):
            for j in xrange(n):
                if A[i][j] in [2, 5, 6]: merge(i * 2, j * 2, -1, 0)
                if A[i][j] in [1, 3, 5]: merge(i * 2, j * 2, 0, -1)
                if A[i][j] in [2, 3, 4]: merge(i * 2, j * 2, 1, 0)
                if A[i][j] in [1, 4, 6]: merge(i * 2, j * 2, 0, 1)
        return find((0, 0)) == find((m * 2 - 2, n * 2 - 2))