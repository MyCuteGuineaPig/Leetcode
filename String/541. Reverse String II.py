"""
541. Reverse String II

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
"""

class Solution:
    def reverseStr(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        i = 0
        s = list(s)
        while i < len(s):
            s[i: i+k] = s[i:i+k][::-1]
            i+=2*k
        return "".join(s)

class Solution(object):
    def reverseStr(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        return s[:k][::-1] + s[k:2*k] + self.reverseStr(s[2*k:], k) if s else ""