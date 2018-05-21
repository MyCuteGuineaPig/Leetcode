"""
105. Construct Binary Tree from Preorder and Inorder Traversal

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

preorder = [3,9,1,2,20,15,7]
inorder = [1,9,2,3,15,20,7]
     3
   /  \
  9    20
 / \  /  \
 1  2 15   7

"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildTree(self, preorder, inorder):
        """
        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        if len(preorder) == 0: return None
        map = collections.defaultdict(int)
        for i, v in enumerate(inorder):
            map[v] = i
        def generater(i,start, end):
            if start > end: return None 
            if start == end: return TreeNode(inorder[start])
            val = preorder[i]
            cur = TreeNode(val)
            cur.left = generater(i+1,start,map[val]-1)
            cur.right = generater(i+map[val]-start+1, map[val]+1, end)
            return cur
        return generater(0,0,len(inorder)-1)