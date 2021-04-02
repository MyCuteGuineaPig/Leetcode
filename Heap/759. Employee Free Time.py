"""
O(NLogK)  K number of employee, N number of schedule
"""
class Solution:
    def employeeFreeTime(self, schedule: '[[Interval]]') -> '[Interval]':
        ans = []
        pq = [(emp[0].start, ei, 0) for ei, emp in enumerate(schedule)]
        heapq.heapify(pq)
        anchor = min(iv.start for emp in schedule for iv in emp)
        while pq:
            start, iid, ind = heapq.heappop(pq)
            if anchor < start:
                ans.append(Interval(anchor, start))
            anchor = max(anchor, schedule[iid][ind].end)
            if ind + 1 < len(schedule[iid]):
                heapq.heappush(pq, (schedule[iid][ind+1].start, iid, ind+1))

        return ans

"""
O(NlogN)
"""
class Solution:
    def employeeFreeTime(self, schedule: '[[Interval]]') -> '[Interval]':
        l = [j for i in schedule for j in i ]
        l.sort(key = lambda x: x.start)
        res = []
        for k,i in enumerate(l):
            if not res or i.start > res[-1].end:
               res.append(i)
            else:
                res[-1].end = max(res[-1].end, i.end)
        return [Interval(i.end, j.start) for i, j in zip(res[:-1], res[1:])]


class Solution:
    def employeeFreeTime(self, schedule: 'list<list<Interval>>') -> 'list<Interval>':
        ints = sorted([i for s in schedule for i in s], key=lambda x: x.start)
        res, end = [], ints[0].end
        for i in ints[1:]:
            if i.start > end:
                res.append(Interval(end, i.start))
            end = max(end, i.end)
        return res