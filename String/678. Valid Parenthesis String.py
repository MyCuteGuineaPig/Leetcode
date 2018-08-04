"""
678. Valid Parenthesis String

Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True

"""

class Solution:
    def checkValidString(self, s):
        """
        :type s: str
        :rtype: bool
        """
        lower = upper = 0
        for i in s:
            lower += 1 if i == '('  else -1
            upper += 1 if i == '(' or i == '*' else  -1 
            if upper < 0: return False 
            lower = max(lower, 0)
        return lower == 0
            

        