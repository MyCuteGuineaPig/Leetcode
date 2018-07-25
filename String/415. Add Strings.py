"""
415. Add Strings

"""


class Solution:
    def addStrings(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        i = len(num1)-1; j = len(num2)-1
        carry = 0
        res = ""
        while i >= 0 or j >= 0 or carry > 0:
            carry += ord(num1[i]) - ord('0') if i >= 0 else 0
            carry += ord(num2[j]) - ord('0') if j >= 0 else 0
            res+=str(carry%10)
            carry //= 10
            i-=1
            j-=1
        return res[::-1]

import itertools
class Solution:
    def addStrings(self, num1, num2):
        z = itertools.zip_longest(num1[::-1], num2[::-1], fillvalue='0')
        res, carry, zero2 = [], 0, 2*ord('0')
        for i in z:
            cur_sum = ord(i[0]) + ord(i[1]) - zero2 + carry
            res.append(str(cur_sum % 10))
            carry = cur_sum // 10
        return ('1' if carry else '') + ''.join(res[::-1])