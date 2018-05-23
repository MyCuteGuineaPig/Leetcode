"""
404. Sum of Left Leaves

"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def sumOfLeftLeaves(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if root is None: return 0
        res = 0
        if root.left and root.left.left is None and root.left.right is None: res+= root.left.val
        return res+self.sumOfLeftLeaves(root.left) + self.sumOfLeftLeaves(root.right) 