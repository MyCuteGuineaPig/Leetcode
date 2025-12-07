"""
assumption: tree 没有cycle
也不需要visited => 因为没有cycle


dfs2 需要preorder process tree, 不可以post order


def dfs2(cur, parent):    -> pre order
    if parent != -1:
        res[cur] += max(res[parent] - max(dp[cur], 0), 0)

    for nxt in graph[cur]:
        if nxt != parent: 
            dfs2(nxt, cur)
   

            
def dfs2(cur, parent):    -> pre order
    for nxt in graph[cur]:
        if nxt != parent: 
            dfs2(nxt, cur)
    if parent != -1:
        res[cur] += max(res[parent] - max(dp[cur], 0), 0)

        1 good 
    /   |     \
   0    2     3 good 
  bad   bad     \ 
                 4 good 

     在3时候，dp 已经包含了 down dp 的结果，所以需要加上up的，
     res[3] +=  res[1] - max(dp[3], 0)

     如果是post order, 3 -》 4, 4进入时候，3 还没有更新res[3], res[3] = 2 
        =》 lead res[4] to wrong result (得到2 而不是3)
        res[4] += res[3] - max(dp[4], 0) =>  += 2 - 1  
   
"""


class Solution:
    def maxSubgraphScore(self, n: int, edges: List[List[int]], good: List[int]) -> List[int]:
        graph = collections.defaultdict(list)
        for e in edges:
            graph[e[0]].append(e[1])
            graph[e[1]].append(e[0])

        dp = [0 for _ in range(n)]
        good = [1 if i == 1 else -1 for i in good]

        def dfs1(cur, parent): # ==> 得到所有dow node 的结果
            tot = 0
            for nxt in graph[cur]:
                if nxt != parent:
                    tot += max(dfs1(nxt, cur), 0)
            dp[cur] = tot + good[cur]
            return dp[cur]

        dfs1(0, -1)
        res = dp[:]

        def dfs2(cur, parent):
            #print(" cur ", cur , " parent ",parent)
            if parent != -1:
                #print("cur ", cur, " parent", parent, "res[parent]", res[parent], "dp[cur]", dp[cur])
                res[cur] += max(res[parent] - max(dp[cur], 0), 0)

            for nxt in graph[cur]:
                if nxt != parent: 
                    dfs2(nxt, cur)

        dfs2(0, -1)
        return res








class Solution:
    def maxSubgraphScore(self, n, edges, good) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        qu = [0]  #topo order
        parent = [-1] * n
        for u in qu:
            for v in adj[u]:
                if v != parent[u]:
                    qu.append(v)
                    parent[v] = u

        dp = [1 if x else -1 for x in good]
        for u in reversed(qu):
            p = parent[u]
            if p != -1:
                dp[p] += max(dp[u], 0)

        ans = dp[:]
        for u in qu:
            p = parent[u]
            if p == -1:
                continue
            high = ans[p] - max(dp[u], 0)
            ans[u] += max(high, 0)

        return ans