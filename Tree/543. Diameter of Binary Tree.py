"""
543. Diameter of Binary Tree

          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
"""

class Solution:
    def diameterOfBinaryTree(self, root):
        def dfs(root):
            if not root:
                return 0, 0
            l, lres =  dfs(root.left)
            r, rres =  dfs(root.right)
            #print(root.val, l, lres, r, rres)
            return 1+max(l, r),max(lres, rres, l + r) 
        return dfs(root)[1]


class Solution:
    def diameterOfBinaryTree(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        return self.depth(root, 0)[1]
    
    def depth(self, root, diameter):
        if not root: 
            return 0, diameter
        left, diameter = self.depth(root.left, diameter)
        right, diameter = self.depth(root.right, diameter)
        return 1 + max(left, right), max(diameter, left + right)  