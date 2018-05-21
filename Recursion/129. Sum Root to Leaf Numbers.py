"""
129. Sum Root to Leaf Numbers

Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.

"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def sumNumbers(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        sum = [0]
        def dfs(root, prev):
            if root is None: return 
            if root.left is None and root.right is None: 
                sum[0]+= prev*10 + root.val 
                return 
            dfs(root.left,prev*10+root.val)
            dfs(root.right,prev*10+root.val)
        dfs(root,0)
        return sum[0]

class Solution:
    def sumNumbers(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        sum = [0]
        def dfs(root, prev):
            if root is None: return 0
            if root.left is None and root.right is None: 
                return prev*10 + root.val 
            return dfs(root.left,prev*10+root.val) + dfs(root.right,prev*10+root.val)
        return dfs(root,0)