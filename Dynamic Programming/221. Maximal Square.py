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
                    
# - 164 ms
class Solution:
    def maximalSquare(self, A):
        for i in range(len(A)):
            for j in range(len(A[i])):
                A[i][j] = int(A[i][j])
                if A[i][j] and i and j:
                    A[i][j] = min(A[i-1][j], A[i-1][j-1], A[i][j-1]) + 1
        return len(A) and max(map(max, A)) ** 2 
        

# Smaller Version - 132 ms
# This version is a bit smaller and faster due to using more of Python and some "tricks":
class Solution:
    def maximalSquare(self, A):
        for i, r in enumerate(A):
            r = A[i] = map(int, r)
            for j, c in enumerate(r):
                if i * j * c:
                    r[j] = min(A[i-1][j], r[j-1], A[i-1][j-1]) + 1
        return max(map(max, A + [[0]])) ** 2



# O(n) Extra Space:  - 128 ms
class Solution:
    def maximalSquare(self, A):
        area = 0
        if A:
            p = [0] * len(A[0])
            for row in A:
                s = map(int, row)
                for j, c in enumerate(s[1:], 1):
                    s[j] *= min(p[j-1], p[j], s[j-1]) + 1
                area = max(area, max(s) ** 2)
                p = s
        return area