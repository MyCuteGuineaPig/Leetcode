class Solution:
    def frogPosition(self, n, edges, t, target):
        if n == 1: return 1.0
        G = [[] for i in range(n + 1)]
        for i, j in edges:
            G[i].append(j)
            G[j].append(i)
        seen = [0] * (n + 1)

        def dfs(i, t):
            if i != 1 and len(G[i]) == 1 or t == 0:
                return i == target
            seen[i] = 1
            res = sum(dfs(j, t - 1) for j in G[i] if not seen[j])
            return res * 1.0 / (len(G[i]) - (i != 1)) #只有是头的位置才减去1
        return dfs(1, t)

class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        if n == 1:
            return 1
        G = collections.defaultdict(list)
        for i, j in edges:
            G[i].append(j)
            G[j].append(i)
        seen = [0 for _ in range(n+1)]
        def f(i, t):
            if i!=1 and len(G[i]) == 1 or t == 0: #增加 i != 1 可能情况是
                """
                     1
                     /
                    2       target = 2, t = 1,  如果只有 len(G[i]) == 1,  到1 直接return 了
                    /
                    3
                   
                """
                return i == target
            seen[i] = 1
            res = max(f(j, t-1) for j in G[i] if not seen[j])
            return res * 1.0 / (len(G[i]) - (i != 1))
        return f(1, t)



class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        nei = collections.defaultdict(set)
        for a, b in edges:
            nei[a].add(b)
            nei[b].add(a)
            
        visited, res = set(), 0.
        def dfs(leaf_id, p, time):
            nonlocal res
            if time >= t:
                if leaf_id == target: res = p
                return
            visited.add(leaf_id)
            neighbors = nei[leaf_id] - visited
            for n in neighbors or [leaf_id]:
                dfs(n, p / (len(neighbors) or 1), time + 1)
        dfs(1, 1, 0)
        return res

#Python 3, BFS without recursion
class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        nei = collections.defaultdict(set)
        for a, b in edges:
            nei[a].add(b)
            nei[b].add(a)
            
        dp = collections.deque([(1, 1, 0)]) # state: leaf_id, possibility, timestamp
        visited = set()
        
        while dp:
            leaf, p, curr = dp.popleft()
            visited.add(leaf)
            
            if curr >= t:
                if leaf == target: return p
                continue
            
            neighbors = nei[leaf] - visited
            for n in neighbors or [leaf]:
                dp += (n, p / (len(neighbors) or 1), curr + 1),
        return 0.


# Python 3, DFS without recursion
class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        nei = collections.defaultdict(set)
        for a, b in edges:
            nei[a].add(b)
            nei[b].add(a)
            
        dp = [(1, 1, 0)] # state: leaf_id, possibility, timestamp
        visited = set()
        
        while dp:
            leaf, p, curr = dp.pop()
            visited.add(leaf)
            
            if curr >= t:
                if leaf == target: return p
                continue
            
            neighbors = nei[leaf] - visited
            for n in neighbors or [leaf]:
                dp += (n, p / (len(neighbors) or 1), curr + 1),
        return 0.


# DFS on tree without recursion
class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        nei = collections.defaultdict(set)
        for a, b in edges:
            nei[a].add(b)
            nei[b].add(a)
                    
        dp = collections.deque([1])
        while dp:
            leaf = dp.popleft()
            for n_ in nei[leaf]:
                nei[n_].remove(leaf)
                dp += n_,
                
        dp = [(1, 1, 0)]
        while dp:
            leaf, p, curr = dp.pop()
            if curr >= t:
                if leaf == target: return p
                continue
            for n in nei[leaf] or [leaf]:
                dp += (n, p / (len(nei[leaf]) or 1), curr+1),
        return 0.0