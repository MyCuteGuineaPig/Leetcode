"""
530. Minimum Absolute Difference in BST
"""
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def getMinimumDifference(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.prev, self.res = float('-infinity'), float('infinity')
        def inorder(root):
            if root:
                inorder(root.left)
                if self.prev!=float('-infinity'):
                    self.res = min(self.res, root.val - self.prev)
                self.prev = root.val
                inorder(root.right)
        inorder(root)
        return self.res


class Solution(object):
    def getMinimumDifference(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        dic, prev, res = [], float('-infinity'),float('infinity')
        while dic or root:
            if root:
                dic.append(root)
                root = root.left
            else:
                root = dic.pop()
                print(root.val, prev)
                if prev != float('infinity'):
                    res = min(res, root.val - prev)
                prev = root.val
                root = root.right
        return res

        

class Solution(object):
    def getMinimumDifference(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        array = []
        def dfs(root):
            if root.left:
                dfs(root.left)
            array.append(root.val)
            if root.right:
                dfs(root.right)
        dfs(root)
        min_diff = min([array[i]-array[i-1] for i in range(1, len(array))])
        return min_diff

class Solution(object):
    def getMinimumDifference(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if not root:
            return 0

        stack = []
        current = root
        res = []
        while current or stack:
            while current:
                stack.append(current)
                current = current.left
            current = stack.pop()
            res.append(current.val)
            current = current.right
            
        ans = min([res[i]-res[i-1] for i in range(1,len(res))])

        return ans
            