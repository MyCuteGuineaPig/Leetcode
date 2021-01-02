"""
# Definition for an interval.
# class Interval(object):
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e
"""
class Solution(object):
    def findRightInterval(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        li = []
        for i,ints in enumerate(intervals):
            li.append([ints.start,i])
        li.sort(key = lambda k: k[0])
        res = []
        for ints in intervals:
            l, r = 0, len(li)
            while l<r:
                mid = (l+r)>>1
                if ints.end<=li[mid][0]:  r = mid
                else: l=mid+1
            if l == len(li): res.append(-1)
            else: res.append(li[l][1])
        return res
        

class Solution(object):
    def findRightInterval(self, intervals):
        start = sorted([ints.start, i] for i, ints in enumerate(intervals)) + [[float('inf'),-1]]
        return [start[bisect.bisect_left(start,[ints.end])][1] for ints in intervals ]





class Solution:
    def findRightInterval(self, intervals):
        l = sorted((e.start, i) for i, e in enumerate(intervals))
        res = []
        for e in intervals:
            r = bisect.bisect_left(l, (e.end,))
            res.append(l[r][1] if r < len(l) else -1)
        return res