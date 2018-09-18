"""
435. Non-overlapping Intervals

Given a collection of intervals, 
find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.

Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]

Output: 1

Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:
Input: [ [1,2], [1,2], [1,2] ]

Output: 2

Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:
Input: [ [1,2], [2,3] ]

Output: 0

Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

"""

class Solution:
    def eraseOverlapIntervals(self, intervals):
        end = float('-inf')
        erased = 0
        for i in sorted(intervals, key=lambda i: i.end):
            if i.start >= end:
                end = i.end
            else:
                erased += 1
        return erased

class Solution:
    def eraseOverlapIntervals(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        if not intervals: return 0
        intervals.sort(key=lambda x: x.start)  # sort on start time
        intervals = iter(intervals)
        currEnd, cnt = next(intervals).end, 0
        for x in intervals:
            if x.start < currEnd:  # find overlapping interval
                cnt += 1
                currEnd = min(currEnd, x.end)  # erase the one with larger end time
            else:
                currEnd = x.end   # update end time
        return cnt

# Definition for an interval.
# class Interval:
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e

class Solution:
    def eraseOverlapIntervals(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        if not intervals: return 0
        intervals.sort(key = lambda x: x.end)
        s, e = intervals[0].start, intervals[0].start
        remove = 0
        for pt in intervals: 
            if pt.start >= e: 
                s = pt.start 
                e = pt.end
            else: 
                s = max(pt.start, s)
                remove += 1
        return remove

class Solution:
    def eraseOverlapIntervals(self, intervals):
        if not intervals: return 0
        intervals.sort(key = lambda x: x.end)
        e = intervals[0].start
        remove = 0
        for pt in intervals: 
            if pt.start >= e: e = pt.end
            else: remove += 1
        return remove



class Solution:
    def eraseOverlapIntervals(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        if not intervals: return 0
        intervals.sort(key = lambda x: x.start)
        s, e = intervals[0].start, intervals[0].start
        remove = 0
        for pt in intervals: 
            if pt.start >= e: 
                s = pt.start 
                e = pt.end
            else: 
                e = min(pt.end, e)
                remove += 1
        return remove