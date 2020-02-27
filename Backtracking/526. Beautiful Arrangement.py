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
        
    
    
    #2020
    class Solution:
    def countArrangement(self, N: int) -> int:
        if not N:
            return 0 
        mylist = [i for i in range(1, N+1)]
        def backTrack(start):
            if start == N:
                return 1 
            res = 0 
            for i in range(start, N):
                if mylist[i] % (start+1) == 0 or (start+1) % mylist[i] == 0:
                    mylist[i],  mylist[start] = mylist[start], mylist[i] 
                    res += backTrack(start+1)
                    mylist[i],  mylist[start] = mylist[start], mylist[i] 
            return res 
        return backTrack(0)
