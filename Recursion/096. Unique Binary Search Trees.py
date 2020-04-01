"""
96. Unique Binary Search Trees
"""
class Solution:
    def numTrees(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [0 for _ in range(n+1)]
        dp[0], dp[1] = 1, 1 
        for i in range(2,n+1):
            for j in range(1,i+1):
                dp[i] += dp[j-1]*dp[i-j]
        return dp[n]

 
# Catalan Number  (2n)!/((n+1)!*n!)  
class Solution:
    def numTrees(self, n):
        return math.factorial(2*n)/(math.factorial(n)*math.factorial(n+1))