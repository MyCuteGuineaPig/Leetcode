"""
671. Second Minimum Node In a Binary Tree
"""

class Solution:
    def findSecondMinimumValue(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if root is None: return -1
        val = [root.val, float("inf")]
        def dfs(root):
            if root is None: return
            if root.val >val[0] and root.val<val[1]:
                val[1] = root.val
            if root.val == val[0]:
                dfs(root.left)
                dfs(root.right)
        dfs(root)
        return -1 if val[1] ==  float("inf") else val[1]