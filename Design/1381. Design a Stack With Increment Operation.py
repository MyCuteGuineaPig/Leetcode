class CustomStack:

    def __init__(self, maxSize: int):
        self.s = []
        self.n = maxSize

    def push(self, x: int) -> None:
        if len(self.s) >= self.n: 
            return 
        self.s.append (x)

    def pop(self) -> int:
        if len(self.s): return self.s.pop()
        return -1

    def increment(self, k: int, val: int) -> None:
        n = len(self.s)
        for i in range(min(k, n)):
            self.s[i] += val



class CustomStack(object):

    def __init__(self, maxSize):
        """
        :type maxSize: int
        """
        self.__max_size = maxSize
        self.__stk = []

    def push(self, x):
        """
        :type x: int
        :rtype: None
        """
        if len(self.__stk) == self.__max_size:
            return
        self.__stk.append([x, 0])

    def pop(self):
        """
        :rtype: int
        """
        if not self.__stk:
            return -1
        x, inc = self.__stk.pop()
        if self.__stk:
            self.__stk[-1][1] += inc
        return x + inc

    def increment(self, k, val):
        """
        :type k: int
        :type val: int
        :rtype: None
        """
        i = min(len(self.__stk), k)-1
        if i >= 0:
            self.__stk[i][1] += val