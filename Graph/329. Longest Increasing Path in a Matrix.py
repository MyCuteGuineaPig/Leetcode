class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        n, m = len(matrix), len(matrix[0])
        dirs = [-1, 0, 1, 0, -1]
        dp = collections.defaultdict(lambda: collections.defaultdict(int))
        def dfs(i, j):
            if j in dp[i]:
                return dp[i][j]
            dp[i][j] = 1
            for a1, a2 in zip(dirs[:-1], dirs[1:]):
                x, y = i + a1, j+a2
                if x < 0 or y < 0 or x >= n or y >= m or matrix[x][y] <= matrix[i][j]:
                    continue
                dp[i][j] = max(dp[i][j], 1+dfs(x,y))
            
            return dp[i][j]
        
        for i in range(n):
            for j in range(m):
                if j not in dp[i]:
                    dfs(i, j)

        res = 1 
        for i, row in dp.items():
            for j, v in row.items():
                res = max(res, v)
        
        return res




class Solution:
    def longestIncreasingPath(self, matrix):
        if not matrix or not matrix[0]:
            return 0
        
        n, m = len(matrix), len(matrix[0])
        dirs = [(-1,0),(1,0),(0,-1),(0,1)]
        
        # Step 1: compute outdegree
        outdegree = [[0]*m for _ in range(n)]
        
        for i in range(n):
            for j in range(m):
                for dx, dy in dirs:
                    x, y = i + dx, j + dy
                    if 0 <= x < n and 0 <= y < m and matrix[x][y] > matrix[i][j]:
                        outdegree[i][j] += 1
        
        # Step 2: start from cells with outdegree = 0
        q = deque()
        for i in range(n):
            for j in range(m):
                if outdegree[i][j] == 0:
                    q.append((i, j))
        
        # Step 3: BFS (level order)
        longest_path = 0
        
        while q:
            longest_path += 1
            for _ in range(len(q)):
                i, j = q.popleft()
                
                for dx, dy in dirs:
                    x, y = i + dx, j + dy
                    if 0 <= x < n and 0 <= y < m and matrix[x][y] < matrix[i][j]:
                        outdegree[x][y] -= 1
                        if outdegree[x][y] == 0:
                            q.append((x, y))
        
        return longest_path