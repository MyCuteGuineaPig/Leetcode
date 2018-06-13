"""
295. Find Median from Data Stream

"""

import heapq
class MedianFinder:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.small  = []  #maxheap #store negative number still
        self.large = [] #minheap
        

    def addNum(self, num):
        """
        :type num: int
        :rtype: void
        """
        if not self.small or -num >= self.small[0]:
            heapq.heappush(self.small, -num)
            if len(self.small) > len(self.large) + 1:
                heapq.heappush(self.large, -heapq.heappop(self.small))
        else: 
            heapq.heappush(self.large,num)
            if len(self.large) > len(self.small):
                heapq.heappush(self.small, -heapq.heappop(self.large))


    def findMedian(self):
        """
        :rtype: float
        """
        return -self.small[0] if len(self.small) > len(self.large) else (self.large[0] - self.small[0])/2
        
        


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()



from heapq import *

class MedianFinder:

    def __init__(self):
        self.heaps = [], []

    def addNum(self, num):
        small, large = self.heaps
        heappush(small, -heappushpop(large, num))
        if len(large) < len(small):
            heappush(large, -heappop(small))

    def findMedian(self):
        small, large = self.heaps
        if len(large) > len(small):
            return float(large[0])
        return (large[0] - small[0]) / 2.0