class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        degree = [0 for _ in range(numCourses)]
        graph = collections.defaultdict(list)
        for p1, p2 in prerequisites:
            graph[p2].append(p1)
            degree[p1] += 1
            
        
        q = deque([])
        for i in range(numCourses):
            if degree[i] == 0:
                q.append(i)
        
        while q: 
            cur = q.popleft()
            for nxt in graph[cur]:
                degree[nxt] -= 1 
                if degree[nxt] == 0:
                    q.append(nxt)
        
        return all (x == 0 for x in degree)
            