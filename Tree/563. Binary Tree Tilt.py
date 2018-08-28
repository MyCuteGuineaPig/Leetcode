"""
563. Binary Tree Tilt

Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
"""


class Solution:
    def findTilt(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfs(root):
            if not root: 
                return 0, 0 
            labs, lsum = dfs(root.left)
            rabs, rsum = dfs(root.right)
            return labs + rabs + abs(lsum - rsum), lsum + rsum + root.val
        return dfs(root)[0]