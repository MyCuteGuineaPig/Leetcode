class Solution:
    def shortestSuperstring(self, A: List[str]) -> str:
        n = len(A)
        shared = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                for k in range(min(len(A[i]), len(A[j])), -1, -1):
                    if A[i][-k:] == A[j][:k]:
                        shared[i][j] = k
                        break

        # The problem becomes finding the shortest path that visits all nodes exactly once.
        # Brute force DFS would take O(n!) time.
        # A DP solution costs O(n^2 2^n) time.
        # 
        # Let's consider integer from 0 to 2^n - 1. 
        # Each i contains 0-n 1 bits. Hence each i selects a unique set of strings in A.
        # Let's denote set(i) => {A[j] | j-th bit of i is 1}
        # dp[i][k] => shortest superstring of set(i) ending with A[k]
        #
        # e.g. 
        #   if i = 6 i.e. 110 in binary. dp[6][k] considers superstring of A[2] and A[1].
        #   dp[6][1] => the shortest superstring of {A[2], A[1]} ending with A[1].
        #   For this simple case dp[6][1] = concatenate(A[2], A[1])
        dp = [[''] * 12 for _ in range(1 << 12)]
        for i in range(1 << n):
            for k in range(n):
                # skip if A[k] is not in set(i) 
                if not (i & (1 << k)):
                    continue
                # if set(i) == {A[k]}
                if i == 1 << k:
                    dp[i][k] = A[k]
                    continue
                for j in range(n):
                    if j == k:
                        continue
                    if i & (1 << j):
                        # the shortest superstring if we remove A[k] from the set(i)
                        s = dp[i - (1 << k)][j]
                        s += A[k][shared[j][k]:]
                        if dp[i][k] == '' or len(s) < len(dp[i][k]):
                            dp[i][k] = s

        min_len = float('inf')
        result = ''

        # find the shortest superstring of all candidates ending with different string
        for i in range(n):
            s = dp[(1 << n) - 1][i]
            if len(s) < min_len:
                min_len, result = len(s), s
        return result





class Solution:
    def shortestSuperstring(self, A: List[str]) -> str:
        n = len(A)
        # Building the graph
        graph = [[0] * n for _ in range(n)]
        for i, word1 in enumerate(A):
            for j, word2 in enumerate(A):
                if i == j: continue
                for k in range(min(len(word1), len(word2)))[::-1]:
                    if word1[-k:] == word2[:k]:
                        graph[i][j] = k
                        break
        
        # Recursion. i is a mask to represent the ordering. k is the last node in the ordering.
        memo = {}
        def search(i, k):
            if (i, k) in memo: return memo[i, k]
            if not (i & (1 << k)): return ''
            if i == (1 << k): return A[k]
            memo[i, k] = ''
            for j in range(n):
                if j != k and i & (1 << j):
                    candidate = search(i ^ (1 << k), j) + A[k][graph[j][k]:]
                    if memo[i, k] == '' or len(candidate) < len(memo[i, k]):
                        memo[i, k] = candidate
            return memo[i, k]
        
        # Finding the best
        res = ''
        for k in range(n):
            candidate = search((1 << n) - 1, k)
            if res == '' or len(candidate) < len(res):
                res = candidate
        return res        


# BFS

class Solution:
    def shortestSuperstring(self, A: List[str]) -> str:
        def getDistance(s1, s2):
            for i in range(1, len(s1)):
                if s2.startswith(s1[i:]):
                    return len(s1) - i
            return 0

        def pathtoStr(A, G, path):
            res = A[path[0]]
            for i in range(1, len(path)):
                res += A[path[i]][G[path[i-1]][path[i]]:]
            return res

        n = len(A)
        G = [[0]*n for _ in range(n)]
        for i in range(n):
            for j in range(i+1, n):
                G[i][j] = getDistance(A[i], A[j])
                G[j][i] = getDistance(A[j], A[i])

        d = [[0]*n for _ in range(1<<n)]
        Q = collections.deque([(i, 1<<i, [i], 0) for i in range(n)])
        l = -1 # record the maximum s_len
        P = [] # record the path corresponding to maximum s_len
        while Q:
            node, mask, path, dis = Q.popleft()
            if dis < d[mask][node]: continue
            if mask == (1<<n) - 1 and dis > l:
                P,l = path,dis
                continue
            for i in range(n):
                nex_mask = mask | (1<<i)
                # case1: make sure that each node is only traversed once
                # case2: only if we can get larger save length, we consider it.
                if nex_mask != mask and d[mask][node] + G[node][i] >= d[nex_mask][i]:
                    d[nex_mask][i] = d[mask][node] + G[node][i]
                    Q.append((i, nex_mask, path+[i], d[nex_mask][i]))

        return pathtoStr(A,G,P)