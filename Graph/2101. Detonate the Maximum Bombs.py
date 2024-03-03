class Solution:
    def maximumDetonation(self, B):
        n, ans, G = len(B), 0, defaultdict(list)
        
        for i in range(n):
            for j in range(n):
                if i == j: continue
                if B[i][2]**2 >= (B[i][0] - B[j][0])**2 + (B[i][1] - B[j][1])**2:
                    G[i] += [j]
        
        
        def dfs(node, visited):
            for child in G[node]:
                if child not in visited:
                    visited.add(child)
                    dfs(child, visited)

        for i in range(n):
            visited = set([i])
            dfs(i, visited)
            ans = max(ans, len(visited))
                          
        return ans