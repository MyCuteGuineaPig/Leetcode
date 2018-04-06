"""
526. Beautiful Arrangement

"""

class Solution:
    def countArrangement(self, N):
        """
        :type N: int
        :rtype: int
        """
        def dfs(n, l):
            if n == 1:
                return 1
            return sum(dfs(n-1,l-{x}) for x in l if x%n == 0 or n%x == 0)
        return dfs(N,set(range(1,N+1)))
        
    