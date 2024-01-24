class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        pq = []
        res = 0
        intervals.sort()
        for i in intervals:
            while pq and pq[0] <= i[0]:
                heapq.heappop(pq)
            heapq.heappush(pq, i[1])
            res = max(res, len(pq))
        return res


class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        res = cur = 0
        print(sorted(x for i,j in intervals for x in [[i, 1], [j, -1]]))
        """
        intervals = [[0,30],[5,10],[15,20]]
        Stdout
        [[0, 1], [5, 1], [10, -1], [15, 1], [20, -1], [30, -1]]
        """
        for i, v in sorted(x for i,j in intervals for x in [[i, 1], [j, -1]]):
            cur += v
            res = max(res, cur)
        return res
