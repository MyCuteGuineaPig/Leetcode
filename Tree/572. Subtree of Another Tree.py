"""
572. Subtree of Another Tree

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.

"""

class Solution:
    def isSubtree(self, s, t):
        """
        :type s: TreeNode
        :type t: TreeNode
        :rtype: bool
        """
        samestructure = lambda na, nb: True if not na and not nb \
                         else False if na and not nb or not na and nb \
                         else na.val == nb.val and samestructure(na.left, nb.left) and samestructure(na.right, nb.right)
        def dfs(s, t):
            return samestructure(s, t) or s and any((dfs(s.left, t), dfs(s.right, t)))
        return dfs(s,t)


class Solution(object):
    def isSubtree(self, s, t):
        def convert(p):
            return "^" + str(p.val) + "#" + convert(p.left) + convert(p.right) if p else "$"    
        return convert(t) in convert(s)


class Solution:
    def isSubtree(self, s, t):
        return self.preorder(s).find(self.preorder(t)) != -1
    
    def preorder(self, node):
        stack, ans = [node], ''
        while stack:
            curr = stack.pop()
            if curr:
                ans += ',%d' % curr.val
                stack.append(curr.right), stack.append(curr.left)
            else:
                ans += ',#'
        return ans
        