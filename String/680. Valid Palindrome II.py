"""
680. Valid Palindrome II

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

"""

class Solution:
    def validPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        i = 0; j = len(s) -1
        while i < j :
            if s[i]!= s[j]: 
                return s[i+1:j+1] == s[i+1:j+1][::-1] or s[i:j] == s[i:j][::-1]
            i+=1; j-=1
        return True


class Solution:
    def validPalindrome(self, s):
        i = 0
        while i < len(s) / 2 and s[i] == s[-(i + 1)]: i += 1
        s = s[i:len(s) - i]
        return s[1:] == s[1:][::-1] or s[:-1] == s[:-1][::-1]