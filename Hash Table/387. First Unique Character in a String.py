"""
387. First Unique Character in a String

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
"""


class Solution:
    def firstUniqChar(self, s):
        """
        :type s: str
        :rtype: int
        """
        dic = collections.Counter(s)
        for i,v  in enumerate(s):
            if dic[v] == 1: 
                return i
        return -1
        