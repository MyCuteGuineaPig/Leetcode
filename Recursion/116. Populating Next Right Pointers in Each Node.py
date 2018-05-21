"""
116. Populating Next Right Pointers in Each Node

Given the following perfect binary tree,

     1
   /  \
  2    3
 / \  / \
4  5  6  7
After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL

Note:

You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).


"""
# Definition for binary tree with next pointer.
# class TreeLinkNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
#         self.next = None


class Solution:
    # @param root, a tree link node
    # @return nothing
    def connect(self, root):
        def dfs(root):
            if root is None or root.left is None: return 
            root.left.next = root.right
            temp = root
            while temp.next:
                temp.right.next = temp.next.left
                temp = temp.next
                temp.left.next = temp.right
            dfs(root.left)
        dfs(root)

class Solution:
    # @param root, a tree link node
    # @return nothing
    def connect(self, root):
        while root and root.left:
            root.left.next = root.right
            temp = root
            while temp.next:
                temp.right.next = temp.next.left
                temp = temp.next
                temp.left.next = temp.right
            root = root.left


"""
阶梯式
"""
class Solution:
    # @param root, a tree link node
    # @return nothing
    def connect(self, root):
        def connectTwo(root1, root2):
            if not root1: return 
            root1.next = root2
            if root1.left:
                connectTwo(root1.left, root1.right)
                connectTwo(root1.right, root2.left)
                connectTwo(root2.left, root2.right)
        if root:
            connectTwo(root.left,root.right)