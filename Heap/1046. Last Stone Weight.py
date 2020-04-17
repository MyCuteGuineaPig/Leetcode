# O(n^2) because bisect.insort is O(n).
class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        stones.sort()
        while len(stones)>1:
            x = stones[-1] - stones[-2]
            stones.pop()
            stones.pop()
            if x:
               bisect.insort(stones,x)

        return stones and stones[0] or 0

class Solution:
    def lastStoneWeight(self, A):
        h = [-x for x in A]
        heapq.heapify(h)
        while len(h) > 1 and h[0] != 0:
            heapq.heappush(h, heapq.heappop(h) - heapq.heappop(h))
        return -h[0]


class Solution:
    def lastStoneWeight(self, A):
            A.sort()
        while len(A) > 1:
            bisect.insort(A, A.pop() - A.pop())
        return A[0]  