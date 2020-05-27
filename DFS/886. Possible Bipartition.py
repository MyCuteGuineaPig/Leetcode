# DFS
class Solution:
    def possibleBipartition(self, N: int, dislikes: List[List[int]]) -> bool:
        mp = collections.defaultdict(list)
        for i, j in dislikes:
            mp[i].append(j)
            mp[j].append(i)
        dp = [0 for _ in range(N+1)]
        def dfs(point, color):
            if dp[point]: 
                return dp[point] == color
            dp[point] = color
            return all( dfs(nxt, -color) for nxt in mp[point])
            
        return all(dfs(i,1) for i in range(1, N+1) if dp[i] == 0)


# BFS

class Solution:
    def possibleBipartition(self, N: int, dislikes: List[List[int]]) -> bool:
        mp = collections.defaultdict(list)
        for i, j in dislikes:
            mp[i].append(j)
            mp[j].append(i)
        
        dp = [0 for _ in range(N+1)]
        for i in range(1, N+1):
            q = collections.deque()
            if dp[i] == 0:
                q.append(i)
            color = 1
            while q:
                size = len(q)
                for _ in range(size):
                    top = q.popleft()
                    dp[top] = color
                    for nxt in mp[top]:
                        if dp[nxt] and dp[nxt] != -color:
                            return False
                        elif dp[nxt] == 0:
                            q.append(nxt)
                color = -color
        
        return True