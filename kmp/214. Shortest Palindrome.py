"""
214. Shortest Palindrome

Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it.
Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
"""

class Solution:
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        snew = s + "#" +s[::-1]
        def getPrefix(snew):
            prefix = [0]*len(snew)
            j = 0
            for i in range(1,len(snew)):
                while j > 0 and snew[i]!=snew[j]:
                    j = prefix[j-1]
                if snew[i] == snew[j]: j+=1
                prefix[i] = j
            return prefix
        kmp = getPrefix(snew)
        nonpal = s[kmp[-1]:]
        return nonpal[::-1] + s


import functools
class Solution:
    def shortestPalindrome(self, s):
        snew = functools.reduce(lambda x, y: x + y + "#", s,"$#")+"^"
        def manacher(snew):
            p = [0]*len(snew)
            mx = id = maxlen = 0
            for i in range(1,len(snew)-1):
                if i < mx: 
                    p[i] = min(p[id*2 - i], p[mx - i])
                else: 
                    p[i] = 1
                while snew[i + p[i]] == snew[i - p[i]]:
                    p[i] += 1
                if p[i] + i > mx:
                    id, mx = i, p[i]+i
                if p[i] == i:
                    maxlen = max(maxlen, p[i]-1)
            return maxlen
        maxlen = manacher(snew)
        nonpal = s[maxlen:]
        return nonpal[::-1] + s

"""

The basic idea is to find the longest palindrome starting from s[0], so that fewest charactors are needed in front of s.

For any charactor(c) in s appearing more than once, define l and r as the first and last index of c, 
then the max length of palindrome starting from s[0] would be no larger than l+r+1, or the first c could never be matched.

For any charactor(c) in s appearing just once, l=r. Here is another key optimization.if s[:l+r+1] is not a palindrome, 
the max length of palindrome starting from s[0] would be no larger than l. 
In other words, c must be excluded from the palindrome, or it could not be matched. 
If s[:l+r+1] is a palindrome, actually c is the center, matched by itself.

"""


class Solution:
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        if not s: return ''
        k=len(s)
        for c in set(s):
            l,r=s.find(c),s.rfind(c)
            k=min(k,l if l==r and s[:l+r+1]!=s[:l+r+1][::-1] else l+r+1)
        for i in range(k,0,-1):
            if s[:i]==s[:i][::-1]: return s[i:][::-1]+s
