"""
100. Same Tree
"""
class Solution:
    def isSameTree(self, p, q):
        """
        :type p: TreeNode
        :type q: TreeNode
        :rtype: bool
        """
        return p is None and q is None or p is not None and q is not None and p.val == q.val and self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
    
        