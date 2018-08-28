"""

623. Add One Row to Tree

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1

"""


class Solution:
    def addOneRow(self, root, v, d):
        """
        :type root: TreeNode
        :type v: int
        :type d: int
        :rtype: TreeNode
        """
        def dfs(root, isleft = True, level = 1):
            if not root:
                if level == d: return TreeNode(v)
                else: return None
            if level == d:
                cur = TreeNode(v)
                if isleft: cur.left = root
                else: cur.right = root
                return cur
            root.left = dfs(root.left, True, level+1)
            root.right = dfs(root.right, False, level+1)
            return root
        return dfs(root)


class Solution:
    def addOneRow(self, root, v, d):
        def dfs(root, level):
            if level <=1:
                cur = TreeNode(v)
                if level == 1: cur.left = root
                else: cur.right = root 
                return cur
            if not root: return None 
            root.left = dfs(root.left, level -1 if level > 2 else 1)
            root.right = dfs(root.right, level -1 if level > 2 else 0)
            return root
        return dfs(root,d)



class Solution:
    def addOneRow(self, root, v, d):
        dummy, dummy.left = TreeNode(None), root
        row = [dummy]
        for _ in range(d - 1):
            row = [kid for node in row for kid in (node.left, node.right) if kid]
        for node in row:
            node.left, node.left.left = TreeNode(v), node.left
            node.right, node.right.right = TreeNode(v), node.right
        return dummy.left #不能用root 因为可能加在最顶层



class Solution:
    def addOneRow(self, root, v, d):
        if d == 1:
            newNode = TreeNode(v)
            newNode.left = root
            return newNode
        
        def recur(root, h, d, v):
            if not root:
                return            
            if h == d - 1:
                duml, dumr = root.left, root.right
                root.left, root.right = TreeNode(v), TreeNode(v)
                root.left.left, root.right.right = duml, dumr
            else:
                recur(root.left, h+1, d, v)
                recur(root.right, h+1, d, v)
            
        recur(root, 1, d, v)
        return root