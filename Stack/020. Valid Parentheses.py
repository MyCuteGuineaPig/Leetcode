"""
20. Valid Parentheses

"""

class Solution:
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stk = []
        dic = {'(': ')', '[': ']', '{': '}'}
        for i in s:
            if i in dic:
                stk.append(i)
            elif not stk or dic[stk.pop()] != i: return False
        return not stk

class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        n = len(s)
        if n == 0:
            return True
        
        if n % 2 != 0:
            return False
            
        while '()' in s or '{}' in s or '[]' in s:
            s = s.replace('{}','').replace('()','').replace('[]','')
        
        if s == '':
            return True
        else:
            return False        