class Solution:
    def minimumSemesters(self, n: int, relations: List[List[int]]) -> int:
        courses = collections.defaultdict(set)
        indegree = [0,]*(n+1)
        for prev, nxt in relations: 
            courses[prev].add(nxt)
            indegree[nxt] += 1
        q = collections.deque([i for i, v in enumerate(indegree)  if v == 0 and i != 0])
        semster = 0
        while q:
            size = len(q)
            for _ in range(size):
                top = q.popleft()
                n-=1
                for next in courses[top]:
                    indegree[next] -= 1
                    if indegree[next] == 0:
                        q.append(next)
            semster += 1
        return semster if n == 0 else -1
