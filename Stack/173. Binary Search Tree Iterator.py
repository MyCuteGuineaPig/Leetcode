
class BSTIterator:

    def __init__(self, root: TreeNode):
        self.stk = []
        self.cur = root        

    def next(self) -> int:
        """
        @return the next smallest number
        """
        val = 0
        while self.cur or self.stk:
            if self.cur:
                self.stk.append(self.cur)
                self.cur = self.cur.left
            else:
                self.cur = self.stk.pop()
                val = self.cur.val
                self.cur = self.cur.right
                break
        return val
    
    def hasNext(self) -> bool:
        """
        @return whether we have a next smallest number
        """
        return self.cur or self.stk
        

#Generator Solution
class BSTIterator:
    def __init__(self, root):
        self.last = root
        while self.last and self.last.right:
            self.last = self.last.right
        self.current = None
        self.g = self.iterate(root)

    # @return a boolean, whether we have a next smallest number
    def hasNext(self):
        return self.current is not self.last

    # @return an integer, the next smallest number
    def next(self):
        return next(self.g)

    def iterate(self, node):
        if node is None:
            return
        for x in self.iterate(node.left):
            yield x
        self.current = node
        yield node.val
        for x in self.iterate(node.right):
            yield x
