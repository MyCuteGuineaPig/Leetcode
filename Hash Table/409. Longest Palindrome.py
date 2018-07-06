"""
409. Longest Palindrome


Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes 
that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
"""
class Solution:
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: int
        """
        dic = collections.Counter(s)
        res, odd = 0, 0
        for v in dic.values():
            res += v - 1 if (v & 1) else v
            odd = odd | (v & 1)
        return res + odd 


class Solution:    
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: int
        """
        tmp = [False] * 58
        res = 0
        for x in s :
            t = ord(x) - 65
            if tmp[t] :
                 res += 2
            tmp[t] = not tmp[t]
        if res != len(s) :
            res += 1 
        return res