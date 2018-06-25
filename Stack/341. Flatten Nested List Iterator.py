"""
341. Flatten Nested List Iterator



Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].


"""

"""
面试的话，不能给constructor push 所有数到stack的解，因为是iterator，不能把所有的数push进数据结构
"""


# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger(object):
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """

class NestedIterator(object):

    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        
        """
        def helper(nl):
            if nl.isInteger():
                self.stack.append(nl.getInteger())
                return
            for i in nl.getList()[::-1]: 
                helper(i)

        self.stack = []
        for i in nestedList[::-1]:
            helper(i)
    

    def next(self):
        """
        :rtype: int
        """
        return self.stack.pop()
        

    def hasNext(self):
        """
        :rtype: bool
        """
        return self.stack

# Your NestedIterator object will be instantiated and called as such:
# i, v = NestedIterator(nestedList), []
# while i.hasNext(): v.append(i.next())



#stack only push current nested list, 而不是一次全部都放进去

class NestedIterator(object):

    def __init__(self, nestedList):
        def helper(nl):
            if nl.isInteger():
                self.stack.append(nl.getInteger())
                return
            for i in nl.getList()[::-1]: 
                helper(i)

        self.stack = []
        for i in nestedList[::-1]:
            self.stack.append(i)
    

    def next(self):
        return self.stack.pop()
        

    def hasNext(self):
        while self.stack:
            if self.stack[-1].isInteger(): return True
            cur = self.stack.pop().getList()[::-1]
            for i in cur:
                self.stack.append(i)
        return False    


"""
不用把所有数都推到stack 里面
数据结构是[nested list & depth], depth用来数是不是到结尾, nested list是存NestedInteger的list
只推当前的nestedList 进stack，当前nested list有children，put它的children 进stack

"""
class NestedIterator(object):

    def __init__(self, nestedList):
        self.stack = [[nestedList,0]]
    

    def next(self):
        res, i = self.stack[-1]
        self.stack[-1][1] += 1
        return res[i].getInteger()
        

    def hasNext(self):
        while self.stack:
            nl, i = self.stack[-1]
            if i == len(nl):
                self.stack.pop()
            elif nl[i].isInteger():
                return True
            else:
                self.stack[-1][1] += 1
                self.stack.append([nl[i].getList(),0])
        return False 



class NestedIterator(object):

    def __init__(self, nestedList):
        def gen(nestedList):
            for x in nestedList:
                if x.isInteger():
                    yield x.getInteger()
                else:
                    for y in gen(x.getList()):
                        yield y
        self.gen = gen(nestedList)

    def next(self):
        return self.value

    def hasNext(self):
        try:
            self.value = next(self.gen)
            return True
        except StopIteration:
            return False