

# O(nlogn) simulation
from sortedcontainers import SortedSet
class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        ct = SortedSet([i for i in range(1,n+1)])
        a = 0
        while len(ct) > 1:
            a = (a + k -1) % len(ct)
            ct.pop(a)
        return ct[0]