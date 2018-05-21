"""

106. Construct Binary Tree from Inorder and Postorder Traversal

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildTree(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: TreeNode
        """
        map = collections.defaultdict(int)
        for i, v in enumerate(inorder):
            map[v] = i
        def generator(i, start, end):
            if start > end:   return None
            if start == end:  return TreeNode(inorder[start])
            val = postorder[i]
            root = TreeNode(val)
            root.right = generator(i-1,map[val]+1,end)
            root.left = generator(i-(end-map[val]+1),start,map[val]-1)
            return root
        return generator(len(inorder)-1,0,len(inorder)-1)
                