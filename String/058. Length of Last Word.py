"""
58. Length of Last Word
"""

class Solution:
    def lengthOfLastWord(self, s):
        """
        :type s: str
        :rtype: int
        """
        li = s.split()
        return len(li[-1]) if li else 0