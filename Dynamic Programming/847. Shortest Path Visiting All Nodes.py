
# Heap
class Solution:
    def shortestPathLength(self, graph):
        memo, final, q = set(), (1 << len(graph)) - 1, [(0, i, 1 << i) for i in range(len(graph))]
        while q:
            steps, node, state = heapq.heappop(q)
            if state == final: return steps
            for v in graph[node]:
                if (state | 1 << v, v) not in memo:
                    heapq.heappush(q, (steps + 1, v, state | 1 << v))
                    memo.add((state | 1 << v, v))

# BFS

class Solution:
    def shortestPathLength(self, graph):
        memo, final, q, steps = set(), (1 << len(graph)) - 1, [(i, 1 << i) for i in range(len(graph))], 0
        while True:
            new = []
            for node, state in q:
                if state == final: return steps
                for v in graph[node]:
                    if (state | 1 << v, v) not in memo:
                        new.append((v, state | 1 << v))
                        memo.add((state | 1 << v, v))
            q = new
            steps += 1

# Deque
class Solution:
    def shortestPathLength(self, graph):
        memo, final, q = set(), (1 << len(graph)) - 1, collections.deque([(i, 0, 1 << i) for i in range(len(graph))])
        while q:
            node, steps, state = q.popleft()
            if state == final: return steps
            for v in graph[node]:
                if (state | 1 << v, v) not in memo:
                    q.append((v, steps + 1, state | 1 << v))
                    memo.add((state | 1 << v, v))




