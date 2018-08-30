"""
655. Print Binary Tree

"""

class Solution:
    def printTree(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[str]]
        """
        def height(root):
            return 0 if not root else 1 + max(height(root.left), height(root.right))
        
        d = height(root)
        self.res = [[""]*(2**d - 1) for _ in range(d)]
        def fill(root, start, end, l):
            if not root: return
            mid = (start+end)//2
            self.res[l][mid] = str(root.val)
            fill(root.left, start, mid-1, l+1)
            fill(root.right, mid+1, end, l+1)
        fill(root, 0, 2**d-1, 0)
        return self.res
        
        