
"""
Solution 1: Can hanle cycle 
[-1,2,-1]
[-1,-1,1]
"""
class Solution:
    
    def validateBinaryTreeNodes(self, n: int, leftChild: List[int], rightChild: List[int]) -> bool:
        class Node: 
            def __init__(self):
                self.left = None
                self.right = None 
                self.parents = None 
            
        node = [Node() for _ in range(n)]
        def dfs(cur, p):
            if node[cur].parents:  #visited before
                return False
            node[cur].parents = p 
            for i, x in enumerate([leftChild[cur], rightChild[cur] ]):
                if x != -1: 
                    if i == 0:
                        node[cur].left = node[x]
                    else:
                        node[cur].right = node[x]
                    if not dfs(x, node[cur])
                        return False
            return True
        for i in range(len(node)):
            if node[i].parents == None:
                if not dfs(i, None): 
                    return False
        
        print([1 if n.parents == None else 0 for n in node ])
        return sum([1 if n.parents == None else 0 for n in node ]) <= 1





#No node should have more than one parent
#There should be exactly one node with zero parents
"""
Below Solution cannot handle cycle
[-1,2,-1]
[-1,-1,1]
"""
import functools
class Solution:
    def validateBinaryTreeNodes(self, n: int, leftChild: List[int], rightChild: List[int]) -> bool:
        parents = [0 for _ in range(n)]
        for i, (l, r) in enumerate(zip(leftChild, rightChild)):
            parents[l] += 1 if l != -1 else 0
            parents[r] += 1 if r != -1 else 0
            if l!=-1 and parents[l] > 1 or r != -1 and parents[r] > 1: 
                return False
        return functools.reduce(lambda x, y: x + (1 if y == 0 else 0), parents, 0) == 1
