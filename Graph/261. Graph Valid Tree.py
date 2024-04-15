# unioin find 
class Solution:
    def validTree(self, n, edges):
        parent = list(range(n))
        def find(x):
            return x if parent[x] == x else find(parent[x])
        def union(xy):
            x, y = map(find, xy)
            parent[x] = y
            return x != y
        return len(edges) == n-1 and all(map(union, edges))

class Solution:
    def validTree(self, n, edges):
        parent = list(range(n))
        def find(x):
            return x if parent[x] == x else find(parent[x])
        for e in edges:
            x, y = map(find, e)
            if x == y:
                return False
            parent[x] = y
        return len(edges) == n - 1


class Solution:
    def validTree(self, n, edges):
        if len(edges) != n - 1:
            return False
        parent = list(range(n))
        def find(x):
            return x if parent[x] == x else find(parent[x])
        def union(xy):
            x, y = map(find, xy)
            parent[x] = y
            return x != y
        return all(map(union, edges))