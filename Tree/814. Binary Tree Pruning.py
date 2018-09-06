"""
814. Binary Tree Pruning


We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    def pruneTree(self, root):
        def dfs(root):
            if not root: return None
            root.left = dfs(root.left)
            root.right = dfs(root.right)
            if not root.left and not root.right and not root.val:
                return None
            return root
        return dfs(root)
        

class Solution:
    def pruneTree(self, root):
        dummy = TreeNode(1)
        dummy.left = root
        stack = [(0, dummy)]
        while stack:
            seen, node = stack.pop()
            if node is None:
                continue
            if not seen:
                stack.extend([(1, node), (0, node.right), (0, node.left)])
            else:
                if node.left and not (node.left.val or node.left.left or node.left.right):
                    node.left = None
                if node.right and not (node.right.val or node.right.left or node.right.right):
                    node.right = None
        return dummy.left 


#对于全是0的tree，返回[0] 而我们需要返回[]
class Solution:
    def pruneTree(self, root):
        def dfs(root):
            if not root: return True
            left = dfs(root.left)
            right = dfs(root.right)
            if left: root.left = None
            if right: root.right = None 
            return left and right and root.val != 1
        dfs(root)
        return root
        