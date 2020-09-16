
class Solution:
    def firstBadVersion(self, n):
        return self.binarySearch(1, n)
    
    def binarySearch(self, low, high):
        if low == high:
            return low
        mid = (low + high)//2
        if isBadVersion(mid) == True:
            return self.binarySearch(low, mid)
        else:
            return self.binarySearch(mid + 1, high)



class Solution:
       def firstBadVersion(self, n):
        return bisect.bisect(type('', (), {'__getitem__': lambda self, i: isBadVersion(i)})(), False, 0, n)


import bisect
class Solution():
    def firstBadVersion(self, n):
        """
        :type n: int
        :rtype: int
        """
        self.__getitem__ = isBadVersion
        return bisect.bisect_left(self, True, 1, n)

class Solution:
    def firstBadVersion(self, n):
        class Wrap:
            def __getitem__(self, i):
                return isBadVersion(i)
        return bisect.bisect(Wrap(), False, 0, n)