"""
606. Construct String from Binary Tree


Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the
"""


class Solution:
    def tree2str(self, t):
        """
        :type t: TreeNode
        :rtype: str
        """
        def dfs(root):
            if not root: return ""
            return str(root.val) + ( "(" + dfs(root.left) +")" if root.left or root.right else "" ) \
             + ( "(" + dfs(root.right) + ")" if root.right else "")
        return dfs(t)


class Solution:
    def tree2str(self, t):
        if not t:
            return ''
        left, right = '', ''
        if t.left or t.right:
            left = '({})'.format(self.tree2str(t.left))
        if t.right:
            right = '({})'.format(self.tree2str(t.right))
        return '{}{}{}'.format(t.val, left, right)

class Solution(object):
    def tree2str(self, t):
        if not t:
            return ""
        res = ""
        left = self.tree2str(t.left)
        right = self.tree2str(t.right)
        if left or right:
            res += "(%s)" % left
        if right:
            res += "(%s)" % right
        return str(t.val) + res