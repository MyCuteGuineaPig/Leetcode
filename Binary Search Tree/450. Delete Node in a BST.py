"""
450. Delete Node in a BST
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

"""
swap key 和比key大的最小值，然后recursively删除swap的值
"""

class Solution:
    def deleteNode(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
        if root:
            if root.val > key:
                root.left = self.deleteNode(root.left,key)
            elif root.val < key:
                root.right = self.deleteNode(root.right, key)
            else:
                if root.left is None and root.right is None:
                    root = None
                elif root.left is None:
                    root = root.right
                elif root.right is None:
                    root = root.left
                else:
                    temp = root.right
                    while temp.left:
                        temp = temp.left
                    temp.val, root.val = root.val, temp.val
                    root.right = self.deleteNode(root.right,temp.val)
        return root

"""
把key的left tree 挂在key->right的leftmost tree下面（比key大的最小数下面）
"""
class Solution:
    def deleteNode(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
        if root:
            if root.val > key:
                root.left = self.deleteNode(root.left,key)
            elif root.val < key:
                root.right = self.deleteNode(root.right, key)
            else:
                if root.left is None and root.right is None:
                    root = None
                elif root.left is None:
                    root = root.right
                elif root.right is None:
                    root = root.left
                else:
                    temp = root.right
                    while temp.left:
                        temp = temp.left
                    temp.left = root.left
                    root = root.right
        return root



