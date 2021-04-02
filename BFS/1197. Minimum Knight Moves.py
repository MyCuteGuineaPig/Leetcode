class Solution:
    def minKnightMoves(self, x: int, y: int) -> int:
        if x == 0 and y == 0:
            return 0
        steps = [[-2,1],[-1,2],[1,2],[2,1],[2,-1],[1,-2]]
        visited = set()
        q = collections.deque([(0,0)]) 
        l = 0
        x, y = abs(x), abs(y)
        while q:
            size = len(q)
            for _ in range(size):
                m, n = q.popleft()
                for i, j in steps:
                    if (m+i,n+j) not in visited and -1 <= m + i <= x+2 and -1 <= n+j <= y + 2:  
                        """
                        需要大于 - 1 原因是 比如 x = 0, y = 1, [0,0] -> [1,2]  -> [-1, 3] - > [0,1] 
                        """
                        if m+i == x and n +j == y:
                            return l + 1
                        visited.add((m+i,n+j))
                        q.append((m+i,n+j))
            l += 1
        return -1

    def minKnightMoves(self, x: int, y: int) -> int:
        @lru_cache(None) 
        def dp(x,y):
            if x + y == 0: return 0
            elif x + y == 2: return 2
            return min(dp(abs(x-1),abs(y-2)), dp(abs(x-2),abs(y-1))) + 1
        return dp(abs(x),abs(y))

"""
Two side BFS
"""
class Solution:
    def minKnightMoves(self, x: int, y: int) -> int:
        x, y = abs(x), abs(y)
        qo = collections.deque([(0, 0, 0)])
        qt = collections.deque([(x, y, 0)])
        do, dt = {(0,0): 0}, {(x,y): 0}
        while True:
            ox, oy, ostep = qo.popleft()
            if (ox, oy) in dt: return ostep + dt[(ox, oy)]
            tx, ty, tstep = qt.popleft()
            if (tx, ty) in do: return tstep + do[(tx, ty)]
            for dx, dy in [(1,2),(2,1),(1,-2),(2,-1),(-1,2),(-2,1),(-1,-2),(-2,-1)]:
                if (ox+dx, oy+dy) not in do and -1 <= ox+dx <= x+2 and -1 <= oy+dy <= y+2:
                    qo.append((ox+dx, oy+dy, ostep+1))
                    do[(ox+dx,oy+dy)] = ostep+1
                if (tx+dx, ty+dy) not in dt and -1 <= tx+dx <= x+2 and -1 <= ty+dy <= y+2:
                    qt.append((tx+dx, ty+dy, tstep+1))
                    dt[(tx+dx,ty+dy)] = tstep+1
        return -1

class Solution:
    def minKnightMoves(self, x: int, y: int) -> int:
        if x == 0 and y == 0:
            return 0
        steps = [[-2,1],[-1,2],[1,2],[2,1],[2,-1],[1,-2],[-1,-2],[-2,-1]]
        visited = set()
        q = collections.deque([(0,0)]) 
        l = 0
        while q:
            size = len(q)
            for _ in range(size):
                m, n = q.popleft()
                for i, j in steps:
                    if (m+i,n+j) not in visited:
                        if m+i == x and n +j == y:
                            return l + 1
                        visited.add((m+i,n+j))
                        q.append((m+i,n+j))
            l += 1
        return -1