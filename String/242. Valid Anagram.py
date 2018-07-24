"""
242. Valid Anagram

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
"""


class Solution:
    def isAnagram(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        return sorted(s) == sorted(t)


import collections
class Solution:
    def isAnagram(self, s, t):
        return collections.Counter(s) == collections.Counter(t)


import collections
class Solution:
    def isAnagram(self, s, t):
        return collections.Counter(s) & collections.Counter(t) ==  collections.Counter(t) ==  collections.Counter(s)