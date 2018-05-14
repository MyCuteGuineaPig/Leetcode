"""
357. Count Numbers with Unique Digits
"""

class Solution:
    def countNumbersWithUniqueDigits(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 0: return 1
        if n > 9: n = 9
        count, accum, tot = 9, 9, 10
        while n>1:
            count, accum, tot, n = count - 1, accum*count, tot + accum*count, n-1
        return tot 