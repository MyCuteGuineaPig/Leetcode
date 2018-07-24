"""
28. Implement strStr()

Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1

"""
class Solution:
    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        return haystack.find(needle)
    

class Solution:
    def strStr(self, haystack, needle):
        if "" == needle: return 0
        kmp = [0]*len(needle)
        j = 0 
        for i in range(1, len(needle)):
            while j > 0 and needle[i]!=needle[j]:
                j = kmp[j-1]
            if needle[i]==needle[j]: j+=1
            kmp[i] = j
        j = 0
        for i in range(len(haystack)):
            while j> 0 and haystack[i] != needle[j]:
                j = kmp[j-1]
            if haystack[i]==needle[j]: j+=1
            if j == len(needle):
                return i - j+1
        return -1