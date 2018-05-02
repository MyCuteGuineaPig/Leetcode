"""
235. Lowest Common Ancestor of a Binary Search Tree
"""
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        minn = min(p.val, q.val)
        maxx = max(p.val,q.val)
        while root.val < minn or root.val>maxx:
            if root.val < minn: root = root.right
            else:  root = root.left
        return root

class Solution(object):
    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode
        """
        if (p.val-root.val)*(q.val-root.val) <= 0:
            return root
        elif p.val < root.val:
            return self.lowestCommonAncestor(root.left,p,q)
        else:
            return self.lowestCommonAncestor(root.right,p,q)
        