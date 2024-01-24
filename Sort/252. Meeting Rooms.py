class Solution:
    def canAttendMeetings(self, intervals: List[List[int]]) -> bool:
        intervals.sort()
        for i, j in zip(intervals[:-1],intervals[1:]):
            if j[0] < i[1]:
                return False
        return True