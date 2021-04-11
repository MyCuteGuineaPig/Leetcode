class Solution:
    def minSideJumps(self, obs: List[int]) -> int:
        dp = [10000000, 1, 0, 1]
        for i in obs:
            dp[i] = 10000000
            for j in range(1, 4):
                if i != j:
                    dp[j] = min(dp[1] + (1 if j != 1 else 0),
                               dp[2] + (1 if j != 2 else 0),
                               dp[3] + (1 if j != 3 else 0))
        return min(dp)


class Solution:
    def minSideJumps(self, obstacles: List[int]) -> int:
        n = len(obstacles)
        
        dp = [[0, ]*3 for i in range(n)]
        dp[0][0] = dp[0][2] = 1
        for i, v in enumerate(obstacles[1:],1):
            if v == 1:
                dp[i][0] = float('inf')
                dp[i][1] = min(dp[i-1][1], dp[i-1][2] + 1)
                dp[i][2] = min(dp[i-1][2], dp[i-1][1] + 1)
            elif v == 2:
                dp[i][1] = float('inf')
                dp[i][0] = min(dp[i-1][0], dp[i-1][2] + 1)
                dp[i][2] = min(dp[i-1][2], dp[i-1][0] + 1)
            elif v==3:
                dp[i][2] =float('inf')
                dp[i][0] = min(dp[i-1][0], dp[i-1][1] + 1)
                dp[i][1] =  min(dp[i-1][1], dp[i-1][0] + 1)
            else:
                dp[i][0] = min(dp[i-1][0], dp[i-1][1] + 1, dp[i-1][2] + 1)
                dp[i][1] =  min(dp[i-1][1], dp[i-1][0] + 1, dp[i-1][2] + 1)
                dp[i][2] = min(dp[i-1][2], dp[i-1][0] + 1, dp[i-1][1] + 1)
            
        return min(dp[-1][0],dp[-1][1],dp[-1][2])



# Top-Down
class Solution:
    def minSideJumps(self, obstacles: List[int]) -> int:
        n = len(obstacles)
        dp = [[-1, ]*3 for i in range(n)]
        def topDown(i, lane):
            if i == 0:
                return 0 if lane == 1 else 1
            if dp[i][lane] != -1:
                return dp[i][lane]
            dp[i][lane] = float('inf')
            if obstacles[i] == lane + 1:
                return dp[i][lane]
            for l in range(3):
                if obstacles[i] != l+1:
                    dp[i][lane] = min(dp[i][lane], topDown(i-1, l)+ (1 if l != lane else 0))
            return dp[i][lane]
                 
        res = min(topDown(n-1, 0), topDown(n-1, 1), topDown(n-1, 2))
        return res


def minSideJumps(self, obstacles: List[int]) -> int:
        dp = [[float('inf')] * 3 for _ in range(len(obstacles))]
        dp[0] = [1, 0, 1]
        
        # run dp process
        for i in range(1, len(obstacles)):
            # 1. fill next position trying to move without side jumps
            for j in range(3):
                if obstacles[i] != j + 1:
                    dp[i][j] = dp[i - 1][j]
            # 2. update dp for i-th position with possible side jumps
            min_cur = min(dp[i])
            for j in range(3):
                if obstacles[i] != j + 1:
                    dp[i][j] = min(dp[i][j], min_cur + 1)
        return min(dp[-1])
