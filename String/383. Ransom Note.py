"""
383. Ransom Note

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

"""

class Solution:
    def canConstruct(self, ransomNote, magazine):
        """
        :type ransomNote: str
        :type magazine: str
        :rtype: bool
        """
        return  collections.Counter(ransomNote) & collections.Counter(magazine) ==  collections.Counter(ransomNote)


class Solution:
    def canConstruct(self, ransomNote, magazine):
        return  collections.Counter(ransomNote) - collections.Counter(magazine) == {}

class Solution:
    def canConstruct(self, ransomNote, magazine):
        return not collections.Counter(ransomNote) - collections.Counter(magazine)