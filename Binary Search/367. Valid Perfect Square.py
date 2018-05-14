"""
367. Valid Perfect Square
"""

class Solution(object):
    def isPerfectSquare(self, num):
        """
        :type num: int
        :rtype: bool
        """
        r = num
        while r*r>num:
            r = (r+num//r)>>1
        return r*r == num