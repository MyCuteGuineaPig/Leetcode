"""
224. Basic Calculator

Example 1:
Input: "1 + 1"
Output: 2

Example 2:
Input: " 2-1 + 2 "
Output: 3

Example 3:
Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23

"""

class Solution:
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        self.stack = []
        i, res, n, sign = 0, 0, len(s), 1
        while i < n:
            if s[i] == '+' or s[i] == '-':
                sign = 1 if s[i] == '+' else -1
            elif s[i] == '(':
                self.stack.append(res)
                self.stack.append(sign)
                sign, res = 1, 0
            elif s[i] == ')':
                res = self.stack.pop()*res
                res += self.stack.pop()
            elif s[i].isdigit():
                val = 0
                while i< n and s[i].isdigit():
                    val = val*10 + int(s[i])
                    i+=1
                res += sign*val
                i-=1
            i+=1
        return res

class Solution:
    def calculate(self, s):
        total = 0
        i, signs, n = 0, [1,1], len(s)
        while i < n:
            if s[i].isdigit():
                start = i 
                while i<n and s[i].isdigit():
                    i+=1
                total += signs.pop()*int(s[start:i])
                continue
            if s[i] in '+-(':
                signs.append(signs[-1]*(1,-1)[s[i] == '-'])
            elif s[i] == ')':
                signs.pop()
            i += 1
        return total