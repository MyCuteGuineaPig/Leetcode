"""
191. Number of 1 Bits
"""



class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        res = 0
        while n:
            res += 1
            n = n & (n-1)
        return res

class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        return sum(b == '1' for b in bin(n)[2:])


class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        return str(bin(n)).count('1')