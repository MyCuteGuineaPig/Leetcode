"""
669. Trim a Binary Search Tree

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1

"""

class Solution:
    def trimBST(self, root, L, R):
        """
        :type root: TreeNode
        :type L: int
        :type R: int
        :rtype: TreeNode
        """
        if root is None: return None
        if root.val < L:
            return self.trimBST(root.right,L,R)
        if root.val > R:
            return self.trimBST(root.left,L,R)
        root.left = self.trimBST(root.left,L,R)
        root.right = self.trimBST(root.right,L,R)
        return root