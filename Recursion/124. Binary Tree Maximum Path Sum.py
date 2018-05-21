"""
124. Binary Tree Maximum Path Sum

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

"""

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        val = [float("-inf")]
        def dfs(root):
            if root is None: return 0
            left =  dfs(root.left)
            right = dfs(root.right)
            cur = max(left+right+root.val, root.val, root.val+left, root.val+right)
            if cur > val[0]:
                val[0] = cur
            return max(max(left,right)+root.val,root.val)
        dfs(root)
        return val[0]  