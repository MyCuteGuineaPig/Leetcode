class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        pq = []
        available_rooms = [i for i in range(n)]
        cnt = [0 for i in range(n)]
        for start, end in sorted(meetings):
            while pq and pq[0][0] <= start:
                _ , room = heapq.heappop(pq)
                heapq.heappush(available_rooms, room)

            if available_rooms:
                room = heapq.heappop(available_rooms)
                heapq.heappush(pq, [end, room])
            else:
                next_end, room = heapq.heappop(pq)
                heapq.heappush(pq, [next_end + (end - start), room])
            cnt[room] += 1 
        return cnt.index(max(cnt))
        