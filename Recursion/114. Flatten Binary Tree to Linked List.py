"""
114. Flatten Binary Tree to Linked List

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

"""
把root 右侧的挂在左侧left tree最下面的
"""

class Solution:
    def flatten(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        def modify(node):
            if node is None: return 
            if node.left:
                if node.right:
                    temp = node.left
                    while temp.right: 
                        temp = temp.right
                    temp.right = node.right
                node.right = node.left
                node.left = None 
            modify(node.right)
        modify(root)

class Solution:
    def flatten(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        def preorder_reverse(node, prev):
            if node is None: return prev 
            prev = preorder_reverse(node.right,prev)
            prev = preorder_reverse(node.left, prev)
            node.right = prev
            node.left = None 
            return node
        preorder_reverse(root, None)


class Solution:
    def flatten(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        if not root:
            return
        self.helper(root)
        
    def helper(self, root):
        if not root or not root.left and not root.right: return root
        left = self.helper(root.left) #返回的是左面最右侧的数，就是左面最大的数
        right = self.helper(root.right)
        if left:
            left.right = root.right
            root.right = root.left
            root.left = None
        if right:  #如果右侧有，右侧一定大于左侧，所以一定是child里最大的数
            return right
        else: return left
