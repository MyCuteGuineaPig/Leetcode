import heapq
class Solution:
    def maxPerformance(self, n: int, speed: List[int], efficiency: List[int], k: int) -> int:
        if k == 0:
            return 0
        res = 0
        s, cur = [], 0
        for i, j in  sorted(zip(speed, efficiency), key = lambda x: -x[1]):
            heapq.heappush(s, i)
            cur += i
            if len(s) > k:
                cur -= heapq.heappop(s)
            res = max(res, cur*j)
        return res%(10**9 + 7)

class Solution:
    def maxPerformance(self, n, speed, efficiency, k):
        h = []
        res = sSum = 0
        for e,s in sorted(zip(efficiency, speed), reverse=1):
            bisect.insort(h, -s) #assume h is sorted, can use binary search to find position to insert
            sSum += s
            if len(h) > k:
                sSum += h.pop()
            res = max(res, sSum * e)
        return res % (10**9+7)