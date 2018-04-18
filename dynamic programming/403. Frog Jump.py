"""
403. Frog Jump
"""
[0,1,3,4,5,7,9,10,12]

"""
timeout solution
"""
class Solution:
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        if stones[1]!=1: 
             return False
        n = len(stones)
        def dfs(beg, gap):
            if beg= = n-1:
                return True
            for i in range(beg+1, n):
                if stones[i] - stones[beg]>gap+1:
                    break
                if gap-1<=  stones[i] - stones[beg] <= gap+1 and dfs(i,stones[i] - stones[beg]):
                    return True
            return False
        return dfs(1,1)
            

import collections
class Solution:
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        if stones[1]!=1: 
            return False
        d = collections.defaultdict(set)
        for i in stones:
            d[i] = set()
        d[1] |= {1}
        for i in range(1,len(stones)):
            for j in d[stones[i]]:
                for k in (j-1, j, j+1):
                    if k>0 and stones[i]+k in d:
                        d[stones[i]+k] |= {k}
        return len(d[stones[-1]]) > 0
        


class Solution:
    def canCross(self, stones):
        """
        :type stones: List[int]
        :rtype: bool
        """
        def dfs(mapp, jump, current, maximum):
            if maximum == current:
                return True
            k3 = current + jump + 1
            k2 = current + jump
            k1 = current + jump - 1
            if k3 in mapp:
                if dfs(mapp, jump+1, k3, maximum):
                    return True
            if jump > 0 and k2 in mapp:
                if dfs(mapp, jump, k2, maximum):
                    return True
            if jump > 0 and k1 in mapp:
                if dfs(mapp, jump-1, k1, maximum):
                    return True
            return False

        for i in range(1, len(stones)):
            if stones[i] > 2*stones[i-1]+1:
                return False
        return dfs(set(stones), 0, 0, stones[-1])
        
    
                               
        