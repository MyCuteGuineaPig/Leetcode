class DisjointSet:
    def __init__(self, n):
        self.rank = [0 for i in range(n)]
        self.size = n
        self.parents = [i for i in range(n)]
    
    def __getitem__(self,x):
        if self.parents[x] != x:
            self.parents[x] = self[self.parents[x]]
        return self.parents[x]

    def union(self,x, y):
        px, py = self[x], self[y]
        if px == py:
            return
        self.size -= 1
        if self.rank[px] > self.rank[py]:
            self.parents[py] = px
        elif self.rank[px] < self.rank[py]:
            self.parents[px] = py
        else:
            self.parents[py] = px
            self.rank[px] += 1

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        n = len(M)
        ds = DisjointSet(n)
        for  i, row in enumerate(M):
            for j, value in enumerate(row[i:],i):
                if value == 1:
                    ds.union(i,j)
        
        return ds.size



import numpy as np

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        return len(set(map(tuple, (np.matrix(M, dtype='bool')**len(M)).A)))
        #.A 表示 matrix to tuple https://numpy.org/doc/stable/reference/generated/numpy.matrix.A.html