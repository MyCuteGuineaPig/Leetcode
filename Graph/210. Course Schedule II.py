class Solution:
    def findOrder(self, numCourses, prerequisites):
        from collections import *
        pre, suc = defaultdict(int), defaultdict(list)
        for a, b in prerequisites:
            pre[a] += 1
            suc[b].append(a)
        free = set(range(numCourses)) - set(pre)
        out = []
        while free:
            a = free.pop()
            out.append(a)
            for b in suc[a]:
                pre[b] -= 1
                pre[b] or free.add(b)
        return out * (len(out) == numCourses)
    

class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        graph = collections.defaultdict(list)
        for prerequisite in prerequisites:
            graph[prerequisite[1]].append(prerequisite[0])

        visited = [0]*numCourses
        onpath = [0]*numCourses
        res = []

        def has_cycle(cur):
            if onpath[cur]:
                return True
            if visited[cur]:
                return False
            visited[cur] = onpath[cur] = True
            for nxt in graph[cur]:
                if not visited[nxt]:
                    if has_cycle(nxt):
                        return True
                elif onpath[nxt]:
                    return True
            res.append(cur)
            onpath[cur] = False
            return False

        
        for i in range(numCourses):
            if not visited[i] and has_cycle(i):
                return []
        
        return res[::-1]