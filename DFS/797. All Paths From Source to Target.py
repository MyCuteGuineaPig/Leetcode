"""
797. All Paths From Source to Target


Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []] 
Output: [[0,1,3],[0,2,3]] 
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.
"""
class Solution:
    def allPathsSourceTarget(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: List[List[int]]
        """
        def dfs(cur, path):
            if cur == len(graph)-1 : res.append(path)
            else:
                for i in graph[cur]: dfs(i,path+[i])

        res = []
        dfs(0,[0])
        return res;

        
class Solution:
    def allPathsSourceTarget(self, g, cur=0):
        if cur == len(g) - 1: return [[len(g) - 1]]
        return [[cur] + path for i in g[cur] for path in self.allPathsSourceTarget(g, i)]
    
    
class Solution:
    def allPathsSourceTarget(self, graph):
		
        res = []
        q = []
        q.append([0,[]])
        n = len(graph)
        
        while q:
            tempNode, route = q.pop(0)
            
            if tempNode == n - 1:
                res.append(route + [tempNode])
                continue
            
            for neighbor in graph[tempNode]:
                q.append([neighbor, route + [tempNode]])
        
        return res
    
 
