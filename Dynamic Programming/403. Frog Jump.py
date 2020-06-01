"""
403. Frog Jump
"""
[0,1,3,4,5,7,9,10,12]

# 2020 TopDown
class Solution:
    def canCross(self, stones: List[int]) -> bool:
        if stones[1]!=1:
            return False
        visited = collections.defaultdict(set)
        stones, last = set(stones), stones[-1]
        def topDown(cur, step):
            if step in visited[cur]:
                return False 
            if cur == last:
                return True 
            for nxt in [step, step+1, step-1]:
                if nxt > 0 and cur + nxt in stones:
                    if topDown(cur+nxt, nxt):
                        return True
            visited[cur].add(nxt)
            return False 
        return topDown(1,1)


# Bottom-up
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
        

    
                               
# 2020 BFS
class Solution:
    def canCross(self, stones: List[int]) -> bool:
        if stones[1]!=1:
            return False
        visited = collections.defaultdict(set)
        stones, last = set(stones), stones[-1]
        
        q = collections.deque([[1,1]])
        while q:
            cur, step = q.popleft()
            if cur == last:
                return True
            for nxt in [step, step+1, step-1]:
                if nxt > 0 and cur + nxt in stones and nxt not in visited[cur+nxt]:
                    visited[cur+nxt] |= {nxt}
                    q.append([cur+nxt, nxt])
        return False