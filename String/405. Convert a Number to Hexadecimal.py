"""
405. Convert a Number to Hexadecimal

Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"

"""

class Solution:
    def toHex(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0: return "0"
        res = ""
        s = "0123456789abcdef"
        while num and len(res)<8:
            res = s[num % 16] + res
            num //=16
        return res

class Solution:
    def toHex(self, num, h=''):
        return (not num or h[7:]) and h or self.toHex(num // 16, '0123456789abcdef'[num % 16] + h)