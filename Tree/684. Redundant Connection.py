"""
684. Redundant Connection

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3

"""


class Solution:
    def findRedundantConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        parent = [i for i in range(len(edges))]
        def find(x):
            if parent[x] == x: return x
            else:
                parent[x] = find(parent[x])
                return parent[x]
        def union(a, b):
            ra, rb = find(a), find(b)
            if ra == rb : return True
            parent[ra] = rb
            return False
        for a, b in edges:
            if union(a-1, b-1):
                return [a,b]

##solution 2
class Solution:
    def findRedundantConnection(self, edges):
        tree = ''.join(map(chr, range(1001)))
        for u, v in edges:
            if tree[u] == tree[v]:
                return [u, v]
            tree = tree.replace(tree[u], tree[v])

##solution 3
class UnionFind:
    def __init__(self, N):
        self.par = list(range(N))
        
    def find(self, x):
        if self.par[x] != x:
            self.par[x] = self.find(self.par[x])
        return self.par[x]
    
    def union(self, x, y):
        self.par[self.find(x)] = self.find(y)

class Solution:
    def findRedundantConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        uf = UnionFind(2 * len(edges))
        
        for v, w in edges:
            if uf.find(v) == uf.find(w):
                return (v,w)
            uf.union(v, w)
        
        return (-1, -1)


##solution 4 union find with rank heuristic
class UnionFind(object):
    def __init__(self):
        self.par = {}
        self.rnk = {}

    def __getitem__(self, x):
        if x not in self.par:
            self.par[x] = x
            self.rnk[x] = 0
        if self.par[x] != x:
            self.par[x] = self[self.par[x]]
        return self.par[x]

    def union(self, x, y):
        xr, yr = self[x], self[y]
        if self.rnk[xr] < self.rnk[yr]:
            self.par[xr] = yr
        elif self.rnk[xr] > self.rnk[yr]:
            self.par[yr] = xr
        else:
            self.par[yr] = xr
            self.rnk[xr] += 1

class Solution(object):
    def findRedundantConnection(self, edges):
        uf = UnionFind()
        for a, b in edges:
            if uf[a] == uf[b]:
                return a, b
            uf.union(a, b)