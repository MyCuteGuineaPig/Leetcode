"""
前提：

即使被mark offline
最初的连接关系仍然存在 属于一个connected component, 去找connected commponent的最小的点

"""

class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        status = [1 for _ in range(c)]
        mp = collections.defaultdict(set)
        for a, b in connections:
            mp[a-1].add(b-1)
            mp[b-1].add(a-1)
        root = collections.defaultdict(int)
        def dfs(cur, src):
            if cur in root:
                return 
            root[cur] = src
            for nxt in mp[cur]:
                dfs(nxt, src)
            return 
        
        for i in range(c):
            dfs(i, i)

        connected_component = [[] for _ in range(c)]
        for i in range(c-1, -1, -1):
            src = root[i]
            # 倒序插入i 到 src
            connected_component[src].append(i)
        

        ret =  []
        for m, a in queries:
            if m == 2:
                status[a-1] = 0 
            elif status[a-1]:
                ret.append(a)
            else:
                src = root[a-1]
                while connected_component[src] and not status[connected_component[src][-1]]:
                    connected_component[src].pop()
                if connected_component[src]:
                    ret.append(connected_component[src][-1] + 1)
                else:
                    ret.append(-1)
        return ret
    

class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        status = [1 for _ in range(c)]
        root = [i for i in range(c)]
        def find(x):
            if root[x] != x:
                root[x] = find(root[x])
            return root[x]
        
        for s, d in connections:
            root_s, root_d = find(s-1), find(d-1)
            if root_s != root_d:
                root[root_s] = root_d
        
        connected_component = collections.defaultdict(list) 
        for i in range(c):
            src = find(i)
            heapq.heappush(connected_component[src], i)

        res = []
        for m, a in queries:
            if m == 2:
                status[a-1] = 0
            elif status[a-1]:
                res.append(a)
            else:
                src = find(a-1)
                while connected_component[src] and not status[connected_component[src][0]]:
                    heapq.heappop(connected_component[src])
                if connected_component[src]:
                    res.append(connected_component[src][0] + 1)
                else:
                    res.append(-1) 
        return res 



class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        status = [1 for _ in range(c)]
        root = [i for i in range(c)]
        def find(x):
            if root[x] != x:
                root[x] = find(root[x])
            return root[x]
        
        for s, d in connections:
            root_s, root_d = find(s-1), find(d-1)
            if root_s != root_d:
                root[root_s] = root_d
        
        connected_component = collections.defaultdict(list) 
        for i in range(c):
            src = find(i)
            heapq.heappush(connected_component[src], i)

        res = []
        for m, a in queries:
            if m == 2:
                status[a-1] = 0
                src = root[a-1]
                connected_component[src].remove(a-1)
                heapq.heapify(connected_component[src])
            elif status[a-1]:
                res.append(a)
            else:
                src = find(a-1)
                if connected_component[src]:
                    res.append(connected_component[src][0] + 1)
                else:
                    res.append(-1) 
        return res 