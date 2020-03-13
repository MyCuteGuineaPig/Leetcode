class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        d = collections.defaultdict(list)
        for i, v in enumerate(manager):
            if v != -1:
                d[v].append(i)

        def f(id):
            if id not in d:
                return 0
            maxt = max( f(nxt) for nxt in d[id]) + informTime[id]
            return maxt        
        return f(headID)

#Smart 
class Solution:
    def numOfMinutes(self, n, headID, manager, informTime):
        def dfs(i):
        if manager[i] != -1:
            informTime[i] += dfs(manager[i])
            manager[i] = -1
        return informTime[i]
    return max(map(dfs, range(n)))

class Solution:
      def numOfMinutes(self, n, headID, manager, informTime):
            children = [[] for i in range(n)]
        for i, m in enumerate(manager):
            if m >= 0: children[m].append(i)

        def dfs(i):
            return max([dfs(j) for j in children[i]] or [0]) + informTime[i]
        return dfs(headID)


class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        def dfs(id: int) -> int:
            return max(informTime[id] + dfs(sub) for sub in subordinates[id]) if id in subordinates else 0
        
        subordinates = collections.defaultdict(list)
        for i, m in enumerate(manager):
            if i != headID:
                subordinates.setdefault(m,[]).append(i)
        return dfs(headID)