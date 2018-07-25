"""
434. Number of Segments in a String

Example:

Input: "Hello, my name is John"
Output: 5

"""

class Solution:
    def countSegments(self, s):
        """
        :type s: str
        :rtype: int
        """
        return len(s.split())

class Solution:
    def countSegments(self, s):
        """
        :type s: str
        :rtype: int
        """
        cnt = 1 if s and s[0]!=' ' else 0
        for i, v in enumerate(s[1:]):
            if s[i]==' ' and s[i+1] != ' ':
                cnt+=1
        return cnt


class Solution:
    def countSegments(self, s):
        return sum(s[i] != ' ' and (i == 0 or s[i-1] == ' ') for i in range(len(s)))