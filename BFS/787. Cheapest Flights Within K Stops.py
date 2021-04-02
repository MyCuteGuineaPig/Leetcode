"""
| Dijkstra's Algorithm

Need two dimensional visited. Or wrong. e.g. 

5
[[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]]
0
2
2
"""

import heapq
class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        dic = collections.defaultdict(list)
        for s, d, p in flights:
            dic[s].append([d, p])
        visited = collections.defaultdict(lambda: collections.defaultdict(int))
        h = [( 0,  src, 0)]  
        visited[src][-1] = 0
        while h:
            time, cur, count = heapq.heappop(h)
            if cur == dst:
                return time
            if count == K+1:
                continue 
            for nei, t in dic[cur]:
                if nei not in visited or count not in visited[nei] or visited[nei][count] > t + time:
                    visited[nei][count] = t+time
                    heapq.heappush(h,(time + t, nei, count+1))
        return -1


import heapq

class Solution:
    
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        
        # Build the adjacency matrix
        adj_matrix = [[0 for _ in range(n)] for _ in range(n)]
        for s, d, w in flights:
            adj_matrix[s][d] = w
            
        # Shortest distances array
        distances = [float("inf") for _ in range(n)]
        current_stops = [float("inf") for _ in range(n)]
        distances[src], current_stops[src] = 0, 0
        
        # Data is (cost, stops, node)
        minHeap = [(0, 0, src)]     
        
        while minHeap:
            
            cost, stops, node = heapq.heappop(minHeap)
            
            # If destination is reached, return the cost to get here
            if node == dst:
                return cost
            
            # If there are no more steps left, continue 
            if stops == K + 1:
                continue
             
            # Examine and relax all neighboring edges if possible 
            for nei in range(n):
                if adj_matrix[node][nei] > 0:
                    dU, dV, wUV = cost, distances[nei], adj_matrix[node][nei]
                    
                    # Better cost?
                    if dU + wUV < dV:
                        distances[nei] = dU + wUV
                        heapq.heappush(minHeap, (dU + wUV, stops + 1, nei))
                    elif stops < current_stops[nei]:
                        
                        #  Better steps?
                        current_stops[nei] = stops
                        heapq.heappush(minHeap, (dU + wUV, stops + 1, nei))
            
        return -1 if distances[dst] == float("inf") else distances[dst]

"""
DFS: 
Complexity:  O(V^2 K)


The number of recursive calls we can potentially make is O(VK).
In each recursive call, we iterate over a given node's neighbors. That takes time O(V) because we are using an adjacency matrix.

 Thus, the overall time complexity is O(V^2 K)

Space Complexity: O(VK + V + E)

O(VK ) is occupied by the memo dictionary and the rest by the adjacency matrix structure we build in the beginning.
"""

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        dic = collections.defaultdict(list)
        for s, d, p in flights:
            dic[s].append([d, p])
        visited = collections.defaultdict(lambda : collections.defaultdict(int))
        def dfs(cur, k):
            #print(cur, k)
            if k <0:
                return -1
            if cur == dst:
                return 0
            if cur in visited and k in visited[cur]:
                return visited[cur][k]
            res = -1
            for nxt, p in dic[cur]:
                ret = dfs(nxt, k-1)
                if ret != -1:
                    if res == -1:
                        res = p+ret
                    else:
                        res = min(res, p+ret)
            visited[cur][k] = res
            return res
        return dfs(src, K+1)