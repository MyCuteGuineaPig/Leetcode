"""
102. Binary Tree Level Order Traversal

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def levelOrder(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if not root: 
            return []
        child, res  = [root], []
        while child:
            res.append([kid.val for kid in child])
            child = [kid for node in child for kid in (node.left, node.right) if kid]
        return res


import collections
class Solution:
    def levelOrder(self, root):
        if not root: 
            return []
        queue = collections.deque([root])
        res = []
        while queue:
            size = len(queue)
            temp = [] 
            for _ in range(size): 
                top = queue.popleft() 
                temp+= [top.val]
                if top.left:
                    queue += [top.left]
                if top.right:
                    queue += [top.right]
            res += [temp]
        return res


from collections import deque
def levelOrder(self, root):
    # traverse in order level, keeping track of (row number, current node)
    queue = deque([(0, root)])
    # keep track of the nodes in each row
    d = {}

    while queue:
        row, node = queue.popleft()
        if node:
            d[row] = d.get(row, []) + [node.val]
            queue += (row+1, node.left), (row+1, node.right)
    # return a list of lists containing node values in increasing order with respect to the row number
    return [d[row] for row in sorted(d.keys())]



class Solution:
    def levelOrder(self, root):
        res = [] 
        def dfs(root, level):
            if not root: 
                return 
            if len(res) <= level:
                res.append([])
            dfs(root.left,level+1)
            res[level].append(root.val)
            dfs(root.right, level+1)
        dfs(root,0)
        return res