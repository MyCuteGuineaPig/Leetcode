"""
43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"

"""

class Solution:
    def multiply(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        li = [0]*(len(num1) + len(num2))
        for i, v in enumerate(reversed(num1)):
            for j, w in enumerate(reversed(num2)):
                n1, n2  = ord(v) - ord('0'), ord(w) - ord('0')
                n1 *= n2
                li[i+j] += n1
                li[i+j+1] += li[i+j]//10
                li[i+j] = li[i+j] % 10
        res = ("".join(map(str,li[::-1]))).lstrip('0')
        return res if res else "0"
