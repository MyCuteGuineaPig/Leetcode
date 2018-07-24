"""
125. Valid Palindrome
"""


class Solution:
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        i, j = 0, len(s)-1
        while i<j:
            while i <j and not s[i].isalnum():
                i+=1
            while i<j and not s[j].isalnum():
                j-=1
            if i>=j: return True
            if s[i].lower()!=s[j].lower():
                return False
            i+=1
            j-=1
        return True

class Solution:
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        alphabet = set()
        letters = "thequickbrownfoxjumpsoverthelazydog0123456789"
        alphabet.update(list(letters))
        s = s.lower()
        s = list(s)
        s = [i for i in s if i in alphabet]
        return s == s[::-1]


class Solution:
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        filtered = re.sub(r'\W+', '', s)
        return filtered.lower() == filtered[::-1].lower()
        
