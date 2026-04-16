class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        
        dp = collections.defaultdict(lambda: collections.defaultdict(lambda: 1e9))
        graph = defaultdict(list)
        for o, c, w in zip(original, changed, cost):
            graph[o].append((c, w))
        for i in range(26): 
            dp[i][i] = 0 

        
        def dijkstra(start, end):
            if dp[start][end] < 1e9 : 
                return dp[start][end]
            dist = collections.defaultdict(lambda: float('inf'))
            pq = [(0,start)]
            dist[start] = 0
            while pq: 
                d, u = heapq.heappop(pq)
                if d > dist[u]: 
                    continue
                if u == end:
                    dp[start][end] = d 
                    return d
                for v, w in graph[u]:
                    if dist[v] > d + w:
                        dist[v] = d + w
                        heapq.heappush(pq, (d+w, v))
            return -1 

        res = 0
        for s,t in zip(source, target):
            cc = dijkstra(s,t)
            if cc == -1:
                return -1
            res += cc 
        
        return res