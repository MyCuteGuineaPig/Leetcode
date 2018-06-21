"""
227. Basic Calculator II


Example 1:

Input: "3+2*2"
Output: 7
Example 2:

Input: " 3/2 "
Output: 1
Example 3:

Input: " 3+5 / 2 "
Output: 5
"""
class Solution:
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        n, i, sign, stk = len(s), 0, 0, []
        while i < n:
            if s[i].isdigit():
                start = i
                while i<n and s[i].isdigit():
                    i+=1
                x = int(s[start:i]) 
                if sign in [0,1]: 
                    stk.append(-x if sign == 1 else x)
                else: 
                    a = stk.pop()
                    stk.append(a*x if sign == 2 else int(a/x))
                continue
            elif s[i] in '+-*/':
                sign = '+-*/'.find(s[i])
            i+=1
        return sum(stk)