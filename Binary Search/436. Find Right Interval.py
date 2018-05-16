"""
436. Find Right Interval
"""
Example 1:
Input: [ [1,2] ]

Output: [-1]

Explanation: There is only one interval in the collection, so it outputs -1.
Example 2:
Input: [ [3,4], [2,3], [1,2] ]

Output: [-1, 0, 1]

Explanation: There is no satisfied "right" interval for [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point;
For [1,2], the interval [2,3] has minimum-"right" start point.
Example 3:
Input: [ [1,4], [2,3], [3,4] ]

Output: [-1, 2, -1]

Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point.

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
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        start = sorted([ints.start, i] for i, ints in enumerate(intervals)) + [[float('inf'),-1]]
        return [start[bisect.bisect_left(start,[ints.end])][1] for ints in intervals ]
        

    def findRightInterval(self, intervals):
    starts = sorted([I.start, i] for i, I in enumerate(intervals)) + [[float('inf'), -1]]
    return [starts[bisect.bisect(starts, [I.end])][1] for I in intervals]
