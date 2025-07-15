"""
至少k个，sort edge, 如果是组成k-1个那个edge value 就是minimum time t
 
"""

class Solution:
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:
        edges.sort(key = lambda x: -x[2]) 
        root = [i for i in range(n)]
        def find(x):
            if root[x]!=x:
                root[x] = find(root[x])
            return root[x]
        rank = [1 for i in range(n)]
        def union(x, y):
            r_x, r_y = find(x), find(y)
            if r_x == r_y: return False
            if rank[r_x] < rank[r_y]:
                root[r_x] = r_y
            elif rank[r_y] < rank[r_x]:
                root[r_y] = r_x 
            else:
                root[r_y] = r_x 
                rank[r_x] += 1  
            return True

        cc = n
        for s, v, d in edges:
            if union(s,v): 
                cc -= 1
                if cc <= k - 1:
                # or 
                # if cc < k:
                    return d
        return 0

