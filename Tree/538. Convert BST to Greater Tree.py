"""
538. Convert BST to Greater Tree

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13

"""


""""
        5 
       /   \ 
      2    13   r = 16, node 13, 
     /    /   \ 
    1    12    16 pre = 0
        pre = 29

"""

class Solution:
    def convertBST(self, root):
        self.pre = 0
        def helper(node):
            if not node: return
            helper(node.right)
            node.val = self.pre + node.val
            self.pre = node.val
            helper(node.left)
        helper(root)
        return root


class Solution:
    def convertBST(self, root):
        def helper(node, pre):
            if not node: return pre
            pre =  helper(node.right, pre)
            node.val += pre
            pre = helper(node.left,node.val)
            return pre
        helper(root, 0)
        return root

class Solution:
    def convertBST(self, root):
        def reverse(root):
            return reverse(root.right) + [root] + reverse(root.left) if root else []
        for a, b in zip(reverse(root), reverse(root)[1:]):
            b.val += a.val
        return root


#BFS
class Solution:
    summ = 0
    def convertBST(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """
        stack = [(root, 0)]
        while stack:
            node, visited = stack.pop()
            if node is None:
                continue
            if visited == 0:
                stack.extend([(node.left, 0), (node, 1), (node.right, 0)])
            else:
                self.summ += node.val
                node.val = self.summ
        return root