"""
617. Merge Two Binary Trees

Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7

"""

#DFS
class Solution:
    def mergeTrees(self, t1, t2):
        """
        :type t1: TreeNode
        :type t2: TreeNode
        :rtype: TreeNode
        """
        def dfs(t1, t2):
            if not t1: return t2
            elif not t2: return t1
            t1.val += t2.val
            t1.left = dfs(t1.left, t2.left)
            t1.right = dfs(t1.right, t2.right)
            return t1
        return dfs(t1, t2)

#BFS
class Solution:
    def mergeTrees(self, t1, t2):
        if not t2: return t1
        if not t1: return t2
        queue = collections.deque()
        queue.append((t1,t2))
        while queue:
            r1, r2 = queue.popleft()
            
            r1.val += r2.val
            if not r1.left:
                r1.left = r2.left
            elif r1.left and r2.left:
                queue.append((r1.left, r2.left))
            
            if not r1.right:
                r1.right = r2.right
            elif r1.right and r2.right:
                queue.append((r1.right, r2.right))

        return t1