"""
032. Longest Valid Parentheses

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
"""
class Solution:
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [0]*(n+1)
        res = 0
        for i in range(1, n):
            if s[i-1] == '(' and s[i] == ')':
                dp[i+1] = dp[i-1] + 2
            elif s[i] == ')' and s[i-1] == ')':
                start = i - dp[i] - 1
                if start>=0 and  s[start] == '(': # start >=0 "(()))())("     ')'的start == -1, (()))
                    dp[i+1] = dp[start] + dp[i] + 2
            res = max(res, dp[i+1])
        return res 


class Solution:
    def longestValidParentheses(self, s):
        n = len(s)
        stk = [-1]
        res = 0
        for i,v in enumerate(s):
            if v == '(':  stk.append(i)
            else:
                stk.pop()
                if not stk:
                    stk.append(i)
                else:
                    res = max(res, i-stk[-1])
        return res 


class Solution:
    # @param s, a string
    # @return an integer
    def longestValidParentheses(self, s):
        longest, last, indices = 0, -1, []
        for i in xrange(len(s)):
            if s[i] == '(':
                indices.append(i)
            elif not indices:
                last = i
            else:
                indices.pop()
                if not indices:
                    longest = max(longest, i - last)
                else:
                    longest = max(longest, i - indices[-1])
        return longest