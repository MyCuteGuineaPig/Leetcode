"""
5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

"""
import functools
class Solution:
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        snew = functools.reduce(lambda x, y: x+y+"#", s, "$#")+"^"
        n, mx, id = len(snew)-1, 0, 0
        res, maxlen = "", 0
        p = [0]*n
        for i in range(1, n):
            p[i] = min(p[2*id - i], mx - i) if i < mx else 1
            while snew [i+p[i]] == snew[i-p[i]]: 
                p[i]+=1
            if p[i] - 1 > maxlen:
                startindex = (i-p[i])//2
                res = s[startindex: startindex + p[i]-1]
                maxlen = p[i] - 1
        return res



class Solution:
    def longestPalindrome(self, s):
        # method 1 
        size = len(s)
        if size == 0 or s == s[::-1]:
            return s
        maxLen = 1
        start = 0
        # 回文串的长度每次要么增加1，要么增加2，要么不增加
        for i in range(size):
            if i - maxLen -1 >= 0 and s[i-maxLen-1:i+1] == s[i-maxLen-1:i+1][::-1]:
                start = i - maxLen - 1
                maxLen += 2
                continue
            if i - maxLen >= 0 and s[i-maxLen:i+1] == s[i-maxLen:i+1][::-1]:
                start = i - maxLen
                maxLen += 1
        return s[start:start+maxLen]