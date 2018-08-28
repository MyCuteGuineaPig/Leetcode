"""
145. Binary Tree Postorder Traversal


Given a binary tree, return the postorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
Follow up: Recursive solution is trivial, could you do it iteratively?

"""
class Solution:
    def postorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        cur = root
        res = []
        while cur: 
            if not cur.right:
                res.append(cur.val)
                cur = cur.left
            else:
                r = cur.right
                while r.left and r.left != cur:
                    r = r.left 
                if not r.left:
                    res.append(cur.val)
                    r.left = cur
                    cur = cur.right
                else:
                    r.left = None
                    cur = cur.left 
        return res[::-1]       

class Solution:
    def postorderTraversal(self, root):
        stack = []
        res = [] 
        cur = root
        while cur or stack:
            if cur: 
                res.append(cur.val)
                stack.append(cur)
                cur = cur.right
            else:
                cur = stack.pop()
                cur = cur.left
        return res[::-1]



class Solution:
    def postorderTraversal(self, root):
        stack = [(root,False)]
        res = [] 
        cur = root
        while stack:
            node, visited = stack.pop()
            if node:
                if visited:
                    res.append(node.val)
                else:
                    stack+=[(node.left, False)]
                    stack+=[(node.right, False)]
                    stack+=[(node, True)]
            
        return res[::-1]



class Solution:
    def postorderTraversal(self, root):
        stack = [root]
        res = [] 
        cur = root
        while stack:
            node = stack.pop()
            if node:
                res.append(node.val)
                stack+=[node.left]
                stack+=[node.right]
        return res[::-1]
            