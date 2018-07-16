"""
693. Binary Number with Alternating Bits


Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101

Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.

Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.

Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
"""

class Solution:
    def hasAlternatingBits(self, n):
        """
        :type n: int
        :rtype: bool
        """
        n ^= n>>2
        return (n & n - 1) == 0


class Solution:
    def hasAlternatingBits(self, n):
        n ^= n>>1
        return (n & n + 1) == 0


class Solution:
    def hasAlternatingBits(self, n):
        return (3*n & 3*n+1 & 3*n + 2  ) == 0