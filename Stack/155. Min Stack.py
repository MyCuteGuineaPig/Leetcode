"""
155. Min Stack

"""


class MinStack:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.stk = []
        self.minstk = []

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """
        self.stk.append(x)
        if not self.minstk or self.minstk[-1] >= x:  #小于等于避免minstack 为null，
            #比如：  ["MinStack","push","push","push","getMin","pop","getMin"]
            #       [[],[0],[1],[0],[],[],[]]  如果只有小于，比如最后pop 一个0，最小的还是0，但是因为minstack 只push了一个0，再pop，minstack为空了
            self.minstk.append(x)
        

    def pop(self):
        """
        :rtype: void
        """
        if self.minstk[-1] == self.stk.pop():
            self.minstk.pop()

    def top(self):
        """
        :rtype: int
        """
        return self.stk[-1]

    def getMin(self):
        """
        :rtype: int
        """
        return self.minstk[-1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()




class MinStack:
    def __init__(self):
        self.min = None
        self.stack = []

    # @param x, an integer
    # @return an integer
    def push(self, x):
        if not self.stack:
            self.stack.append(0)
            self.min = x
        else:
            self.stack.append(x - self.min)
            if x < self.min:
                self.min = x

    # @return nothing
    def pop(self):
        x = self.stack.pop()
        if x < 0:
            self.min = self.min - x

    # @return an integer
    def top(self):
        x = self.stack[-1]
        if x > 0:
            return x + self.min
        else:
            return self.min

    # @return an integer
    def getMin(self):
        return self.min