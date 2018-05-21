"""
111. Minimum Depth of Binary Tree111. Minimum Depth of Binary Tree

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.

"""

class Solution:
    def minDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if root is None: return 0
        if root.left is None: return 1+self.minDepth(root.right)
        if root.right is None: return 1+self.minDepth(root.left)
        return 1+min(self.minDepth(root.left), self.minDepth(root.right))

class Solution:
    def minDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        queue = collections.deque()
        if root:
            queue.append(root)
        level = 0
        while len(queue) > 0:
            level += 1
            size = len(queue)
            for i in range(size):
                cur = queue.popleft()
                if not cur.left and not cur.right:
                    return level
                if cur.left: 
                    queue.append(cur.left)
                if cur.right:
                    queue.append(cur.right)
        return 0