"""
520. Detect Capital


Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False


"""

class Solution:
    def detectCapitalUse(self, word):
        """
        :type word: str
        :rtype: bool
        """
        count = sum(1 for i in word if i.isupper())
        return count == len(word) or count == 0 or count == 1 and word[0].isupper()

class Solution:
    def detectCapitalUse(self, word):
        """
        :type word: str
        :rtype: bool
        """
        if word.upper() == word:
            return True
        elif word[1:].lower() == word[1:]:
            return True
        else:
            return False

class Solution:
    def detectCapitalUse(self, word):
        return word.isupper() or word.islower() or word.istitle()