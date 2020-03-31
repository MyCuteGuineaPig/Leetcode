"""
546. Remove Boxes
"""
import collections;
class Solution:
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        dp = collections.defaultdict(int)
        def dfs(i,j,k):
            if i>j: return 0
            if dp[(i,j,k)]>0: return dp[(i,j,k)]
            while i<j and boxes[j-1] == boxes[j]:
                k += 1; j-=1;
            dp[(i,j,k)] = (k+1)**2 + dfs(i,j-1,0)
            for x in range(i,j):
                if boxes[x] == boxes[j]:
                    dp[(i,j,k)] = max(dp[(i,j,k)], dfs(i,x,k+1)+dfs(x+1,j-1,0))
            return dp[(i,j,k)]
        return dfs(0, len(boxes)-1, 0)


import collections;
class Solution:
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        dp = collections.defaultdict(int)
        def dfs(i,j,k):
            if i>j: return 0
            if i == j: return (k+1)**2
            if dp[(i,j,k)]>0: return dp[(i,j,k)]
            while i<j and boxes[j-1] == boxes[j]:
                k += 1; j-=1;
            dp[(i,j,k)] = (k+1)**2 + dfs(i,j-1,0)
            for x in range(i,j):
                if boxes[x] == boxes[j]:
                    dp[(i,j,k)] = max(dp[(i,j,k)], dfs(i,x,k+1)+dfs(x+1,j-1,0))
            return dp[(i,j,k)]
        return dfs(0, len(boxes)-1, 0)