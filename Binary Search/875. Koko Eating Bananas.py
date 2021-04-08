class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        def isok(k):
            count = 0
            for p in piles:
                count += (p - 1) // k + 1
            return count <= h
        l = 1
        r = max(piles)
        while l < r:
            mid = (l + r)//2
            if isok(mid):
                r = mid 
            else:
                l = mid + 1 
        return l
                
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        l, r = 1, max(piles)
        while l < r:
            m = (l + r) // 2
            if sum((p + m - 1) // m  for p in piles) > h:
                l = m + 1
            else:
                r = m
        return l


class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        def isok(k):
            count = 0
            for p in piles:
                if p <= k:
                    count += 1
                else:
                    count += p // k + (1 if p % k != 0 else 0)
            return count <= h
        l = 1
        r = max(piles)
        while l < r:
            mid = (l + r)//2
            if isok(mid):
                r = mid 
            else:
                l = mid + 1 
        return l
                