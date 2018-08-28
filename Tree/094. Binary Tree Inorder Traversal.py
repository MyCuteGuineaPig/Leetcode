"""
94. Binary Tree Inorder Traversal

iven a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
Follow up: Recursive solution is trivial, could you do it iteratively?

"""


class Solution:
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur = root
        res = []
        while cur: 
            if not cur.left:
                res.append(cur.val)
                cur = cur.right
            else:
                pre = cur.left
                while pre.right and pre.right != cur:
                    pre = pre.right
                if not pre.right: 
                    pre.right = cur 
                    cur = cur.left
                else:
                    res.append(cur.val)
                    cur = cur.right
                    pre.right = NULL
        return res


class Solution:
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack = [(root, False)]
        res = []
        while stack:
            node, visited =stack.pop()
            if node:
                if visited:
                    res.append(node.val)
                else:
                    stack.append((node.right, False))
                    stack.append((node, True))
                    stack.append((node.left, False))
        return res



class Solution:
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack = []
        res = []
        cur = root
        while cur or stack:
            if cur: 
                stack.append(cur)
                cur = cur.left 
            else:
                cur = stack.pop()
                res.append(cur.val)
                cur = cur.right
        return res