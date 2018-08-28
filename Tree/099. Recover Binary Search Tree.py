"""
99. Recover Binary Search Tree


Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?


"""
# 顺序一定是inorder!!!!
class Solution:
    def recoverTree(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        self.first, self.last, self.pre =  None, None, None
        def dfs(root):
            if not root: return
            dfs(root.left)
            if self.pre and root.val < self.pre.val:
                if not self.first:
                    self.first = self.pre
                self.last = root
            self.pre = root
            dfs(root.right)
                
        dfs(root)
        self.first.val, self.last.val = self.last.val, self.first.val




class Solution:
    def recoverTree(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        first, last = None, None
        cur = root
        prev = None
        while cur: 
            if not cur.left:
                if prev and prev.val > cur.val:
                    if not first: 
                        first = prev
                    last = cur
                prev = cur
                cur = cur.right
            else:
                l = cur.left
                while l.right and l.right != cur:
                    l = l.right
                if not l.right: 
                    l.right = cur
                    cur = cur.left
                else:
                    if prev and prev.val > cur.val:
                        if not first: 
                            first = prev
                        last = cur
                    prev.right = None
                    prev = cur
                    cur = cur.right
        first.val, last.val = last.val, first.val



class Solution:
    def recoverTree(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        cur = root
        
        start = end = None
        
        stack = []
        result = []
        while cur or stack:
            while cur:
                stack.append(cur)
                cur = cur.left
            
            cur = stack.pop()
            if result: 
                if start is None and cur.val < result[-1].val:
                    start = result[-1]
                if start and cur.val > start.val:
                    end = result[-1]
                    start.val, end.val = end.val, start.val
                    return 
                
            result.append(cur)
            cur = cur.right
        
        if end is None:
            end = result[-1]
            start.val, end.val = end.val, start.val
        
        return 