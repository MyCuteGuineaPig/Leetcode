class Solution:
    def alienOrder(self, words: List[str]) -> str:
        graph = collections.defaultdict(set)
        degree = collections.defaultdict(int)

        for word in words:
            for c in word:
                degree[c] = 0

        for prev, cur in zip (words[:-1], words[1:]):
            min_size = min(len(prev), len(cur))
            for i, (a, b) in enumerate(zip(prev,cur)):
                if a != b: 
                    if b not in graph[a]: #avoid same path insert twice
                        graph[a].add(b)
                        degree[b] += 1
                    break
                elif i == min_size -1 and len(prev) > len(cur):
                    return ""

        q = deque()
        res = []
        for c, v in degree.items():
            if v == 0:
                q.append(c)
                
        while q:
            cur = q.popleft()
            res.append(cur)
            for nxt in graph[cur]:
                degree[nxt] -= 1
                if degree[nxt] == 0:
                    q.append(nxt)
        
        
        return "".join(res) if len(degree) == len(res) else ""
    


class Solution:
    def alienOrder(self, words: List[str]) -> str:
        graph = collections.defaultdict(set)
        on_path = collections.defaultdict(bool)
        visited =  collections.defaultdict(bool)

        for word in words:
            for c in word:
                on_path[c] = False
                visited[c] = False

        for prev, cur in zip (words[:-1], words[1:]):
            min_size = min(len(prev), len(cur))
            for i, (a, b) in enumerate(zip(prev,cur)):
                if a != b: 
                    if b not in graph[a]: #avoid same path insert twice
                        graph[a].add(b)
                    break
                elif i == min_size -1 and len(prev) > len(cur):
                    return ""
        
        res = []
        def has_cycle(cur):
            on_path[cur] = visited[cur] = True
            for nxt in graph[cur]:
                if not visited[nxt]:
                    if has_cycle(nxt):
                        return True
                elif on_path[nxt]:
                    return True
            on_path[cur]=False
            res.append(cur)
            return False
        
        for c in visited.keys():
            if not visited[c] and has_cycle(c):
                return ""

        return "".join(res[::-1]) if len(visited) == len(res) else ""