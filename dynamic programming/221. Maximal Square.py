class Solution:
    def maximalSquare(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if(len(matrix)==0): return 0
        dp = [0 for _ in range(len(matrix[0])+1)]
        res = 0
        for i, row in enumerate(matrix):
            prev = 0
            for j, num in enumerate(row):
                if num == '1':
                    dp[j+1], prev = min(dp[j],dp[j+1],prev)+1, dp[j+1]
                    res = max(res,dp[j+1])
                else:
                    dp[j+1] = 0
        return res**2
                    