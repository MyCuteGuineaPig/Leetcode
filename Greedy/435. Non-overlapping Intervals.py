

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