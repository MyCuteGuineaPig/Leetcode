"""
101. Symmetric Tree


For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        def helper(left, right):
            return (not left and not right) or left is not None and right is not None and left.val == right.val and helper(left.left, right.right) and helper(right.left,left.right)
        return not root or helper(root.left, root.right)


class Solution:
    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        if root is None: return True
        stk = []
        stk.append(root.left)
        stk.append(root.right)
        while stk:
            right = stk.pop()
            left = stk.pop()
            if left is None and right is None: continue
            if left is None or right is None or left.val != right.val:
                return False
            stk.append(right.left)
            stk.append(left.right)
            stk.append(left.left)   
            stk.append(right.right)
        return True