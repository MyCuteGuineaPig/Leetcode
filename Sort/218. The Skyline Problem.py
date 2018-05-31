"""
218. The Skyline Problem
"""

import heapq
class Solution:
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        heap = []
        i, n = 0, len(buildings)
        skyline = []
        while i<n or len(heap)>0:
            cur_x = -heap[0][1] if heap else buildings[i][0]
            if i==n or cur_x < buildings[i][0]:    
                while len(heap)>0 and -heap[0][1] <= cur_x:
                    heapq.heappop(heap)
            else:
                cur_x = buildings[i][0]
                while i<n and cur_x  == buildings[i][0]:
                    heapq.heappush(heap,[-buildings[i][2],-buildings[i][1]])
                    i+=1
            cur_h = -heap[0][0] if heap else 0
            if len(skyline) == 0 or skyline[-1][1]!=cur_h:
                skyline += [[cur_x, cur_h]]
        return skyline 

class Solution(object):
    def getSkyline(self, buildings):
        """
        :type buildings: List[List[int]]
        :rtype: List[List[int]]
        """
        cp= set([b[0] for b in buildings]+[b[1] for b in buildings])
        i, active, res = 0, [], []
        for c in sorted(cp):
            while i<len(buildings) and buildings[i][0]<=c:
                heapq.heappush(active, (-buildings[i][2], buildings[i][1]))
                i+=1

            while active and active[0][1]<=c:
                heapq.heappop(active)

            h= len(active) and -active[0][0]
            if not res or h!=res[-1][1]:
                res.append([c, h])
        return res



class Solution(object):
    def getSkyline(self, buildings):
        events = sorted([(L, -H, R) for L, R, H in buildings] + list(set((R, 0, None) for L, R, H in buildings)))
        res, hp = [[0, 0]], [(0, float("inf"))]
        for x, negH, R in events:
            while x >= hp[0][1]: 
                heapq.heappop(hp)
            if negH: heapq.heappush(hp, (negH, R)) #如果有height push进q
            if res[-1][1] + hp[0][0]: #避免现hp中最大height个 res上一个height一样
                res += [x, -hp[0][0]],
        return res[1:]
"""
input 
[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]

events:
[(2, -10, 9), (3, -15, 7), (5, -12, 12), (7, 0, None), (9, 0, None), (12, 0, None), (15, -10, 20), (19, -8, 24), (20, 0, None), (24, 0, None)]


"""