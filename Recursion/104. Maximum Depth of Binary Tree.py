"""
104. Maximum Depth of Binary Tree
"""

class Solution:
    def maxDepth(self, root):
        return 0 if root is None else 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))