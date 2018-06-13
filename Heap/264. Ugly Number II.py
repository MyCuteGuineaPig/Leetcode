"""
264. Ugly Number II

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
"""

#DP
class Solution:
    def nthUglyNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [1]
        p2 = p3 = p5 = 0
        for _ in range(n-1):
            dp.append(min(dp[p2]*2, dp[p3]*3, dp[p5]*5))
            if dp[-1] == dp[p2]*2:
                p2 += 1
            if dp[-1] == dp[p3]*3:
                p3+=1
            if dp[-1] == dp[p5]*5:
                p5+=1
        return dp[-1]

#heap

import heapq
class Solution:
    def nthUglyNumber(self, n):
        heap = [1]
        for _ in range(n):
            top = heapq.heappop(heap)
            if top % 2 == 0:
                heapq.heappush(heap,top*2)
            elif top % 3 == 0:
                heapq.heappush(heap,top*2) 
                heapq.heappush(heap,top*3)
            else:
                heapq.heappush(heap,top*2)
                heapq.heappush(heap,top*3)
                heapq.heappush(heap,top*5)
        return top

class Solution:
    def nthUglyNumber(self, n):
        ugly = [1]
        i2 = i3 = i5 = 0
        while len(ugly) < n:
            while ugly[i2] * 2 <= ugly[-1]: i2 += 1
            while ugly[i3] * 3 <= ugly[-1]: i3 += 1
            while ugly[i5] * 5 <= ugly[-1]: i5 += 1
            ugly.append(min(ugly[i2] * 2, ugly[i3] * 3, ugly[i5] * 5))
        return ugly[-1]