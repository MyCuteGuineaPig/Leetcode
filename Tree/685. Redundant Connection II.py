"""
685. Redundant Connection II

Example 1:
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
"""
import collections
class Solution:
    def findRedundantDirectedConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        dic = collections.defaultdict(int)
        parent = [i for i in range(len(edges))]
        deleted = [] #删除的node，如果删除错了，还有cycle, 返回没删除的
        for e in edges:
            if e[1] not in dic:
                dic[e[1]] = e[0]
            else:
                deleted = [e[0], e[1]] 
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        for e in edges:
            if e == deleted: continue
            roota, rootb = find(e[0]-1), find(e[1]-1)
            if roota == rootb:
                if deleted: return [dic[deleted[1]], deleted[1]] #删错了
                else: return e #没有duplicate
            parent[rootb] = roota
        return deleted #删除对了，或者根本就没有cycle