class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        if not matrix:
            return 0
        m,n = len(matrix), len(matrix[0])
        dp = [[0 for _ in range(n)] for _ in range(m)]
        res = 0
        for i, row in enumerate(matrix):
            for j, k in enumerate(row):
                if k==0:
                    continue 
                dp[i][j] = 1
                if i>0 and j > 0 and matrix[i-1][j] == matrix[i][j-1] == matrix[i-1][j-1] == 1:
                        dp[i][j] +=  min(dp[i-1][j-1],dp[i][j-1],dp[i-1][j])
                res += dp[i][j]
        return res

#TOP-Down DP


class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])

        @functools.lru_cache(None) # use this for memory search
        def dp(i,j):
            if matrix[i][j]==1 : 
                if i!=0 and j!=0:
                    return min(dp(i-1,j), dp(i,j-1), dp(i-1,j-1))+1
                else:
                    return 0+1
            else:
                return 0
        
        return sum(dp(i,j) for i in range(m) for j in range(n))


