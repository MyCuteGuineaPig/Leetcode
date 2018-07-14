"""
342. Power of Four
"""

class Solution:
    def isPowerOfFour(self, n):
        """
        :type num: int
        :rtype: bool
        """
        return n>0 and (n-1)%3 == 0 and (n&n-1) == 0