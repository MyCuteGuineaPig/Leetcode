"""
226. Invert Binary Tree

Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1

"""

class Solution:
    def invertTree(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        def revert(node):
            if not node: return 
            node.left, node.right = node.right, node.left
            revert(node.left)
            revert(node.right)
        revert(root)
        return root

class Solution:
    def invertTree(self, root):
        if not root: return None
        root.left,root.right = self.invertTree(root.right), self.invertTree(root.left)
        return root



class Solution: 
    def invertTree(self, root):
        if root:
            invert = self.invertTree
            root.left, root.right = invert(root.right), invert(root.left)
            return root

class Solution:
    def invertTree(self, root):
        queue = collections.deque([(root)])
        while queue:
            node = queue.popleft()
            if node:
                node.left, node.right = node.right, node.left
                queue.append(node.left)
                queue.append(node.right)
        return root

class Solution:
    def invertTree(self, root):
        stack = [root]
        while stack:
            node = stack.pop()
            if node:
                node.left, node.right = node.right, node.left
                stack += node.left, node.right
        return root