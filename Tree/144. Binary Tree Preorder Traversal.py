"""
144. Binary Tree Preorder Traversal

Given a binary tree, return the preorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
Follow up: Recursive solution is trivial, could you do it iteratively?

"""

class Solution:
    def preorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        res = []
        cur = root
        while cur: 
            if not cur.left:
                res.append(cur.val)
                cur = cur.right
            else:
                pre = cur.left
                while pre.right and pre.right != cur:
                    pre = pre.right
                if not pre.right:
                    res.append(cur.val) #第一次的pass 就加上
                    pre.right = cur
                    cur = cur.left
                else:
                    pre.right = None  #重复pass parent，不加
                    cur = cur.right
        return res


class Solution:
    def preorderTraversal(self, root):
        res = []
        stack = [] 
        cur = root
        while cur or stack: 
            if cur: 
                res.append(cur.val)
                stack.append(cur)
                cur = cur.left 
            else:
                cur = stack.pop()
                cur = cur.right
        return res


class Solution:
    def preorderTraversal(self, root):
        res = []
        stack = [(root, False)] 
        cur = root
        while stack: 
            node, visited = stack.pop() 
            if node: 
                if visited: 
                    res.append(node.val)
                else:
                    stack.append((node.right,False))
                    stack.append((node.left, False))
                    stack.append((node,True))
        
        return res



class Solution:
    def preorderTraversal(self, root):
        ret = []
        stack = [root]
        # iteratively through the stack
        while stack:
            node = stack.pop()
            if node:
                ret.append(node.val)
                stack.append(node.right)
                stack.append(node.left)
        return ret

class Solution:
    def preorderTraversal(self, root):
        return [] if root is None else [root.val]+self.preorderTraversal(root.left)+self.preorderTraversal(root.right)