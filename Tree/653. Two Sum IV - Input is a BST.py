"""
653. Two Sum IV - Input is a BST


Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
"""

#DFS 
class Solution:
    def findTarget(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: bool
        """
        li = []
        def traverse(root):
            if not root: 
                return
            traverse(root.left)
            li.append(root.val)
            traverse(root.right)
        traverse(root)
        i, j = 0, len(li) - 1
        while i <j:
            tmp = li[i] + li[j]
            if tmp < k: i+=1
            elif tmp > k: j-=1
            else: return True
        return False

#BFS

class Solution:
    def findTarget(self, root, k):
        if not root: return False
        bfs, s = [root], set()
        for i in bfs:
            if k - i.val in s: return True
            s.add(i.val)
            if i.left: bfs.append(i.left)
            if i.right: bfs.append(i.right)
        return False


#BST Iterator
class BSTIterator:
    def __init__(self,root, isleft):
        self.tree = root
        self.isleft = isleft
        self._val = None
        self.stack = []
        self.cur = root
        self.__next__()
    
    @property
    def val(self,):
        return self._val
    
    @val.setter
    def val(self, value):
        self._val = value

    def __next__(self,):
        while self.stack or self.cur:
            if self.cur:
                self.stack.append(self.cur)
                self.cur = self.cur.left if self.isleft else self.cur.right
            else:
                self.cur = self.stack.pop()
                self._val = self.cur.val 
                self.cur = self.cur.right if self.isleft else self.cur.left
                break

class Solution:
    def findTarget(self, root, k):
        l = BSTIterator(root, True)
        r = BSTIterator(root, False)
        while l.val < r.val: 
            tmp = l.val + r.val 
            if tmp < k:
                next(l)
            elif tmp > k:
                next(r)
            else: return True
        return False