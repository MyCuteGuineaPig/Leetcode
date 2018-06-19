"""
150. Evaluate Reverse Polish Notation

Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
"""

import operator
class Solution:
    def evalRPN(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """
        stk, operators = [], {"+": operator.add, "-": operator.sub, "*": operator.mul, "/": operator.truediv}
        for i in tokens:
            if i not in operators:
                stk.append(int(i))
            else: 
                b, a = stk.pop(), stk.pop()
                stk.append(int(operators[i](a,b)))
        return stk[-1]


class Solution:
    def evalRPN(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """
        op = {'+': lambda x: lambda y: int(x + y),
              '-': lambda x: lambda y: int(x - y),
              '*': lambda x: lambda y: int(x * y),
              '/': lambda x: lambda y: int(x / y)}
        
        stack = []
        for t in tokens:
            if t not in ('+', '-', '*', '/'):
                stack.append(int(t))
            else:
                r, l  = stack.pop(), stack.pop()
                stack.append(op[t](l)(r))
        
        return stack.pop()