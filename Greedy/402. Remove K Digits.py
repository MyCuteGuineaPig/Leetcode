"""

402. Remove K Digits

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.

Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

"""
class Solution:
    def removeKdigits(self, num, k):
        out = []
        for d in num:
            while k and out and out[-1] > d:
                out.pop()
                k -= 1
            out.append(d)
        return ''.join(out[:-k or None]).lstrip('0') or '0'
"""
case when k = 0, out[:-0] returns no elements, but -0 or None evaluates to None, 
and out[:None] returns the entire list!

"""


class Solution:
    def removeKdigits(self, num, k):
        n = len(num)
        if n == k: return "0"
        stack = []
        kk = k
        for i in num: 
            while stack and k and stack[-1] > i:
                stack.pop()
                k -= 1 
            stack.append(i)
        return str(int("".join(stack[:n-kk])))
        
class Solution:
    def removeKdigits(self, num, k):
        n = len(num)
        if n == k: return "0"
        stack = []
        kk = k
        for i in num: 
            while stack and k and stack[-1] > i:
                stack.pop()
                k -= 1 
            if stack or not stack and i != '0':
                stack.append(i)
        return "".join(stack[:n-kk] if stack else ['0'])
                

class Solution(object):
    def removeKdigits(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        while k > 0:
            k -= 1
            i = 0
            while i < len(num)-1:
                if num[i] > num[i+1]:
                    break
                i += 1
            num = num[:i] + num[i+1:]
        
        if len(num) == 0:
            return "0"
        else:
            return str(int(num))

"""
Regex
"""
class Solution:
    def removeKdigits(self, num, k):
        sub = re.compile('1[0]|2[01]|3[0-2]|4[0-3]|5[0-4]|6[0-5]|7[0-6]|8[0-7]|9[0-8]|.$').sub
        # $ 表示string 的结尾
        for _ in range(k):
            num = sub(lambda m: m.group()[1:], num, 1)
        return num.lstrip('0') or '0'