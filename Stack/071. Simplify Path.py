"""
71. Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
"""

class Solution:
    def simplifyPath(self, path):
        """
        :type path: str
        :rtype: str
        """
        stk = []
        for i in path.split('/'):
            if i =='..':
                if stk: stk.pop()
            elif i!='.' and i:
                stk.append(i) 
        return "/" + "/".join(stk)