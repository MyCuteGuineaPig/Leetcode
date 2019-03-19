
"""

Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
 

Note:

graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
"""

# write by own
class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        color = collections.defaultdict(lambda: -1)
        
     def dfs(start, cur_color):
            color[start] = cur_color
            return all(dfs(i,  1-cur_color) if color[i] == -1 else color[i]^color[start] for i in graph[start] )
        
        return all(dfs(i, 0) for i, edges in enumerate(graph) if color[i] == -1)
    

#BFS
class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n, color= len(graph), {}
        for i in range(n):
            if i not in color and graph[i]:
                color[i] = 1;
                c = 0
                q = collections.deque([i])
                while q: 
                    size = len(q)
                    for _ in range(size):
                        cur = q.popleft()
                        for nb in graph[cur]:
                            if nb not in color: 
                                color[nb] = c 
                                q.append(nb)
                            elif color[nb] != c:
                                return False
                    c = 1-c
        return True    
    

class Solution:
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        color = collections.defaultdict(lambda:-1)
        return all(self.dfs(graph, v, edges, 0, color) for v, edges in enumerate(graph) if color[v] == -1)
    
    def dfs(self, graph,v, edges, cur_color, color):
        if color[v]!=-1: return color[v] == cur_color
        color[v] = cur_color
        return all(self.dfs(graph, e, graph[e], int(not cur_color), color) for e in edges)
