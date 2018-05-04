"""
352. Data Stream as Disjoint Intervals

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
"""
# Definition for an interval.
# class Interval(object):
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e

class SummaryRanges(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.heap = []

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        if val not in (x[0] for x in self.heap):
            heapq.heappush(self.heap, (val, Interval(val, val)))

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        stack = []
        while self.heap:
            val, cur = heapq.heappop(self.heap)
            if not stack:
                stack.append((val,cur))
            else:
                _, prev = stack[-1]
                if cur.start <= prev.end+1:
                    prev.end = max(prev.end, cur.end)
                else:
                    stack.append((val,cur))
        self.heap = stack
        return list(map(lambda x: x[1], stack))

        


# Your SummaryRanges object will be instantiated and called as such:
# obj = SummaryRanges()
# obj.addNum(val)
# param_2 = obj.getIntervals()

class SummaryRanges:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.dic = []
        

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        def upper_bound(target):
            left, right = 0, len(self.dic)-1
            while left<=right:
                mid = int(left + (right-left)/2)
                if self.dic[mid].start>target:
                    right = mid - 1
                else:
                    left = mid + 1
            return left 
        i = upper_bound(val)
        if i!=0 and self.dic[i-1].end+1>=val:
            i-=1
        start, end = val, val
        while i<len(self.dic) and end+1>=self.dic[i].start: #现在的结束加1，大于下一个开始，比如[1,2] 和[3,3] 要结合成[1,3]
            end = max(end, self.dic[i].end)
            start = min(start,self.dic[i].start)
            del self.dic[i]
        self.dic.insert(i,Interval(start, end))

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        return self.dic



class SummaryRanges:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.dic = []
        

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        def upper_bound(target):
            left, right = 0, len(self.dic)-1
            while left<=right:
                mid = int(left + (right-left)/2)
                if self.dic[mid].end>target:  #用end 比较也可以，想找到点离target最近的
                    right = mid - 1
                else:
                    left = mid + 1
            return left 
        i = upper_bound(val)
        if i!=0 and self.dic[i-1].end+1>=val:
            i-=1
        start, end = val, val
        while i<len(self.dic) and end+1>=self.dic[i].start:
            end = max(end, self.dic[i].end)
            start = min(start,self.dic[i].start)
            del self.dic[i]
        self.dic.insert(i,Interval(start, end))

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        return self.dic
