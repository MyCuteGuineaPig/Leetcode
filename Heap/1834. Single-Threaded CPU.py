class Solution:
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        h = [[e, t, ind] for ind, (e, t) in enumerate(tasks)]
        h.sort()
        
        q = []
        index = 0
        res = []
        time = 1
        while q or index < len(h):
            while index < len(h) and h[index][0] <= time:
                heapq.heappush(q, [h[index][1], h[index][2], h[index][0]])
                index += 1
            
            if q:
                process, ind, enq = heapq.heappop(q)
                res.append(ind)
                time += process
            else:
                time = h[index][0]
        return res
            

class Solution:
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        h = [[e, t, ind] for ind, (e, t) in enumerate(tasks)]
        h.sort()
        
        q = []
        index = 0
        res = []
        while q or index < len(h):
            if not q:
                start = h[index][0]
                while index < len(h) and h[index][0] == start:
                    heapq.heappush(q, [h[index][1], h[index][2], h[index][0]])
                    index += 1
            else:
                process, ind, enq = heapq.heappop(q)
                res.append(ind)
                start = max(start, enq) + process
                while index < len(h) and h[index][0] <= start:
                    heapq.heappush(q, [h[index][1], h[index][2], h[index][0]])
                    index += 1

        return res