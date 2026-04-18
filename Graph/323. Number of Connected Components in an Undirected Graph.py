class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        graph = collections.defaultdict(list)
        visited = [0]*n
        for s, e in edges:
            graph[s].append(e)
            graph[e].append(s)
        
        def dfs(s, p):
            visited[s] = True
            for nxt in graph[s]:
                if not visited[nxt]:
                    dfs(nxt, s)
                    
        
        res = 0
        for i in range(n):
            if not visited[i]:
                dfs(i, -1)
                res += 1 
        
        return res
    

class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        parents = [i for i in range(n)]

        def find(cur):
            if parents[cur] == cur:
                return cur
            parents[cur] = find(parents[cur])
            return parents[cur]
        
        for s, e in edges:
            p0, p1 = find(s), find(e)
            if p0 != p1 : 
                n -= 1 
            parents[p1] = p0
        
        return  n