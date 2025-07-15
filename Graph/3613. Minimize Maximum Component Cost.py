"""
组成最多k个，不能少于min(k, n)个， 如果少于，有的大的edge value没有被remove
只要有小的value edge组成k个connected components，剩下的点就不需要了

必须先sort 再去找点
到k个connected component 最后一个增加的edge 就是最大的点

不能先连接，再去找点
比如  graph 是  
     
     0 - (45) -> 1 - (81) -> 2 - (76) -> 3 
                 1 ----- (48) ---------->3
     0 ----------------(12) -----------> 3

     如果 k = 1,  12-> 45 -> 48 -> 76 (return 76)
     如果 k = 3, 12 (return 12)  把1和3连起来了， 0, 2 单独
"""

class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        edges.sort(key=lambda x: x[2])
        root = [i for i in range(n)]
        cc = [n] 
        # 假设所有点都是独立的，cc = n， 连上两个点减去1 
        if k >= n:
            return 0
        def find(x):
            if root[x]!=x:
                root[x] = find(root[x])
            return root[x]
        def union(x, y):
            r_a, r_b = find(x), find(y)
            if r_a == r_b:
                return False 
            root[r_a] = r_b
            cc[0] -= 1 
            return True 
        for s, v, d in edges:
            if union(s,v) and cc[0] == k:
                return d 
        return 0



class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        graph = collections.defaultdict(lambda: defaultdict(int))
        l , r = 0, 0
        for s, t, d in edges:
            graph[s][t] = d
            graph[t][s] = d 
            r = max(r, d)
        
        def dfs(cur, par, visited, cur_graph):
            if visited[cur]:
                return
            visited[cur] = 1 
            for nxt in cur_graph[cur]:
                if nxt == par: continue 
                dfs(nxt, cur, visited, cur_graph)
            return

        def check(mid):
            cur_graph = collections.defaultdict(set)
            for x, mp in graph.items():
                for y, d in graph[x].items():
                    if d <= mid:
                        cur_graph[x].add(y)
                        cur_graph[y].add(x)
            
            cc = 0
            visited = [0 for i in range(n)]
            # 数有几个connected components
            for i in range(n):
                if visited[i] == 0: 
                    cc += 1 
                    dfs(i, i, visited, cur_graph)
            return cc <= k

        while l < r: 
            mid = (l+r) // 2 
            if check(mid):
                r = mid
            else : 
                l = mid + 1 
        return l