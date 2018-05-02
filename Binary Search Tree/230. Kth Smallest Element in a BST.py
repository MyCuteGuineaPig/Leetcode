"""
230. Kth Smallest Element in a BST
"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def kthSmallest(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        lis = []
        def inorder(root):
            if root:
                inorder(root.left)
                lis.append(root.val)
                inorder(root.right)
        inorder(root)
        return lis[k-1]

"""
iterative
"""
class Solution:
    def kthSmallest(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        stack = []
        stack.append(root)
        while len(stack):
            if root:
                stack.append(root)
                root = root.left
            else:
                root = stack[-1]
                stack.pop()
                k -= 1
                if k == 0:
                    return root.val
                root = root.right
        return -1