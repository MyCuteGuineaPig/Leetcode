"""
392. Is Subsequence

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.
"""

class Solution:
    def isSubsequence(self, s, t):
        it = iter(t)
        return all(S in it for S in s)

class Solution:
    def isSubsequence(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """

        t_idx = -1
        for c in s:
            t_idx = t.find(c, t_idx + 1)
            if t_idx == -1:
                return False
        return True

class Solution(object):
    def isSubsequence(self, s, t):
        if not s:
            return True

        i = 0
        for c in t:
            if c == s[i]:
                i += 1
            if i == len(s):
                break
        return i == len(s)