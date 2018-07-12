"""
201. Bitwise AND of Numbers Range


Example 1:

Input: [5,7]
Output: 4
Example 2:

Input: [0,1]
Output: 0
"""


class Solution:
    def rangeBitwiseAnd(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """
        c = 0
        while n!= m: 
            n >>= 1
            m >>= 1
            c += 1
        return m <<c


class Solution:
    def rangeBitwiseAnd(self, m, n):
        c = 0
        while n!= m: 
            n &= ~(1<<c)
            m &= ~(1<<c)
            c += 1
        return m