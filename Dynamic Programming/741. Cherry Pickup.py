"""
741. Cherry Pickup
"""
class Solution:
    def cherryPickup(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        if grid[0][0] == -1 or grid[n-1][n-1] == -1: return 0
        dp = [[-1,]*n for _ in range(n)] # 很重要，
        """
        因为比如[[1,-1,1],[-1,1,1],[1,1,1]]， 
        如果初始化为0，k=1 后 , dp = [[-1,-1,0],[-1,-1,0],[0, 0,0]]
        然后k = 2, i = 2, j = 2, 只能从(1,0) (1,0) 过来, dp[1][1] = -1，但是因为初始化为0,通过比较max，所以dp最后应该为-1，但是结果为0
        
        """
        dp[0][0] = grid[0][0]
        for k in range(1,2*n-1):
            for i in range(min(k,n-1),max(-1, k-n),-1):
                for j in range(min(k,n-1),max(-1, k-n),-1):
                    if grid[i][k-i] == -1 or grid[j][k-j] == -1:
                        dp[i][j] = -1
                        continue
                    if i>0 : dp[i][j] = max(dp[i][j], dp[i-1][j]) #向下向右
                    if j>0 : dp[i][j] = max(dp[i][j], dp[i][j-1]) #向右向下
                    if i>0 and j>0: dp[i][j] = max(dp[i][j], dp[i-1][j-1]) #向下向下
                    if dp[i][j]<0 :continue
                    dp[i][j] += grid[i][k-i]
                    if i!=j:
                         dp[i][j] += grid[j][k-j]
        return max(dp[-1][-1],0)
                    
                        
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == -1 or grid[n-1][n-1] == -1: return 0
        dp = [[-1,]*n for _ in range(n)]
        
        dp[0][0] = grid[0][0]
        for k in range(1,2*n-1):
            for i in range(n-1,-1,-1):
                for j in range(n-1,-1,-1):
                    
                    p, q = k-i, k -j
                    if p < 0 or p >= n or q<0 or q>=n or grid[i][p] == -1 or grid[j][q] == -1:
                        dp[i][j] = -1
                        continue
                    if i>0 : dp[i][j] = max(dp[i][j], dp[i-1][j]) #向下向右
                    if j>0 : dp[i][j] = max(dp[i][j], dp[i][j-1]) #向右向下
                    if i>0 and j>0: dp[i][j] = max(dp[i][j], dp[i-1][j-1]) #向下向下
                    if dp[i][j]<0 :continue
                        
                    dp[i][j] += grid[i][p]
                    if i!=j:
                         dp[i][j] += grid[j][q]
        return max(dp[-1][-1],0)


# Top-Down
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        N = len(grid)
        lookup = {}
        
        def solve(x1, y1, x2, y2):
            # check if we reached bottom right corner
            if x1 == N-1 and y1 == N-1: 
                return grid[x1][y1] if grid[x1][y1] != -1 else float("-inf")
            
            # out of the grid and thorn check
            if x1 == N or y1 == N or x2 == N or y2 == N or grid[x1][y1] == -1 or grid[x2][y2] == -1: 
                return float("-inf")
            
			# memorization check
            lookup_key = (x1, y1, x2, y2)
            if lookup_key in lookup: return lookup[lookup_key]
            
			# pick your cherries
            if x1 == x2 and y1 == y2:
                cherries = grid[x1][y1]
            else:
                cherries = grid[x1][y1] + grid[x2][y2]
                
            res = cherries + max(
                solve(x1 + 1, y1, x2 + 1, y2),  # right, right
                solve(x1, y1 + 1, x2, y2 + 1),  # down, down
                solve(x1 + 1, y1, x2, y2 + 1),  # right, down
                solve(x1, y1 + 1, x2 + 1, y2), # down, right
            )
            
            lookup[lookup_key] = res
            return res
        
        res = solve(0, 0, 0, 0)
        return res if res > 0 else 0