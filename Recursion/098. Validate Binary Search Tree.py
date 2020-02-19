"""
98. Validate Binary Search Tree
"""
"""
recursion
"""
class Solution:
    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        val = [float('-inf')]
        def inorder(root):
            if root is None: 
                return True
            if inorder(root.left) is False: return False
            if root.val<=val[0]:
                return False
            val[0] = root.val
            return inorder(root.right) 
        return inorder(root)

"""
iterative
"""

class Solution:
    def isValidBST(self, root):
        stk = []
        val = float("-inf")
        while len(stk)>0 or root is not None:
            if root:
                stk.append(root)
                root = root.left
            else:
                root = stk.pop()
                if root.val <= val:
                    return False
                val = root.val
                root = root.right
        return True
