"""
222. Count Complete Tree Nodes

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6

"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def countNodes(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def get_height(root):
            return -1 if not root else 1 + get_height(root.left)
        cnt = 0
        while root:
            hl, hr = get_height(root.left), get_height(root.right)
            if hl == hr:
                cnt += 1<<(1+hl)
                root = root.right
            else:
                cnt += 1<<(1+hr)
                root = root.left
        return cnt


class Solution:
    def countNodes(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        h = self.get_height(root)
        return 0 if h<0 else (1<<h) + self.countNodes(root.right) if h-1 == self.get_height(root.right) else (1<<(h-1)) + self.countNodes(root.left)
        
    def get_height(self,root):
        return -1 if not root else 1 + self.get_height(root.left)



"""
不用重复算h,每次自动减1
"""
class Solution:
    def countNodes(self, root):
        if not root:
            return 0
        h = height(root)
        res = 0
        while root:
            if height(root.right) == h-1:
                res += 1<<h
                root = root.right
            else:
                res += 1<<(h-1)
                root = root.left
            h -= 1
            
        return res

def height(node):
    if not node:
        return -1
    else:
        return 1+height(node.left)