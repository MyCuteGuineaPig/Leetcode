"""
313. Super Ugly Number

Example:

Input: n = 12, primes = [2,7,13,19]
Output: 32 
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
             super ugly numbers given primes = [2,7,13,19] of size 4.
"""

class Solution:
    def nthSuperUglyNumber(self, n, primes):
        """
        :type n: int
        :type primes: List[int]
        :rtype: int
        """
        dp = [1]
        pt = [0]*len(primes)
        for _ in range(n-1):
            minv = float('inf')
            minid = []
            for i,v in enumerate(primes):
                if v*dp[pt[i]] < minv:
                    minv = v*dp[pt[i]]
                    minid = [i]
                elif  v*dp[pt[i]] == minv:
                    minid.append(i)
            dp.append(minv)
            for i in minid:
                pt[i] += 1
        return dp[-1]

import heapq
class Solution:
    def nthSuperUglyNumber(self, n, primes):
        heap = [i for i in primes]
        ugly = 1
        for _ in range(1, n):
            ugly = heapq.heappop(heap)
            ind = 0
            for i, v in enumerate(primes):
                if ugly % v == 0:
                   ind = i
                   break
            for v in primes[:ind+1]:
                heapq.heappush(heap,ugly*v)
        return ugly

      
class Solution:
    def nthSuperUglyNumber(self, n: int, primes: List[int]) -> int:
        if n == 1 : return 1
        q = [i for i in primes]
        for _ in range(n-2):
            top = heapq.heappop(q)
            for i, v in enumerate(primes):
                if top % v == 0:
                    for p in primes[:i+1]:
                        heapq.heappush(q, p*top)
                    break

        return q[0]
