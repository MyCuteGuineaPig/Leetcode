"""
110. Balanced Binary Tree

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.

"""
class Solution:
    def isBalanced(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        def get_height(root):
            if root is None: return 0
            left = get_height(root.left)
            right = get_height(root.right)
            if left == -1 or right == -1 or abs(left-right)>1:
                return -1
            return 1+max(left,right)
        return True if get_height(root) != -1 else False

"""
Iterative, based on postorder traversal:
"""

class Solution(object):
    def isBalanced(self, root):
        stack, node, last, depths = [], root, None, {}
        while stack or node:
            if node:
                stack.append(node)
                node = node.left
            else:
                node = stack[-1]
                if not node.right or last == node.right: #last是比如向右了，然后返回

                """
                     1
                    / \
                   2   2
                  / \
                 3   3
                / \
               4   6
                    比如从3到6，node = 3, last = 4, 并且有right，所以node = node.right = 6

                    到Node =6, last = 4, 并且有没有right, 更新last = 6,
                    然后返回3, 3->right = 6, 进去if 避免重复进入right

                """
                    node = stack.pop()
                    left, right  = depths.get(node.left, 0), depths.get(node.right, 0)
                    if abs(left - right) > 1: return False
                    depths[node] = 1 + max(left, right)
                    last = node
                    node = None
                else:
                    node = node.right
        return True