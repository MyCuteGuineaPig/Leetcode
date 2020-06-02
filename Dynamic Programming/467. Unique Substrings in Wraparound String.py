"""
467. Unique Substrings in Wraparound String

"""
import collections
class Solution:
    def findSubstringInWraproundString(self, p):
        """
        :type p: str
        :rtype: int
        """
        if len(p)==0 : return 0
        letters, length,res = collections.defaultdict(int), 1, 1
        letters[p[0]] = 1
        for i in range(1,len(p)):
            if ord(p[i]) - ord(p[i-1]) != 1 and (p[i-1]!='z' or p[i] != 'a'): 
                length = 0
            length += 1 
            if letters[p[i]] < length :
                letters[p[i]], res = length, res + length - letters[p[i]]
        return res

from collections import defaultdict
class Solution(object):
    def findSubstringInWraproundString(self, p):
        """
        :type p: str
        :rtype: int
        """
        if len(p) <= 1:
            return len(p)
        count = defaultdict(int)
        max_length = 1
        count[p[0]] = 1
        match = "zabcdefghijklmnopqrstuvwxyz"
        for i in range(1, len(p)):
            if p[i-1] + p[i] in match:
                max_length += 1
            else:
                max_length = 1
            count[p[i]] = max(count[p[i]], max_length)
        return sum(count.values())



class Solution:
    def findSubstringInWraproundString(self, p):
        res = {i: 1 for i in p}
        l = 1
        for i, j in zip(p, p[1:]):
            l = l + 1 if (ord(j) - ord(i)) % 26 == 1 else 1
            res[j] = max(res[j], l)
        return sum(res.values())


#Two Pointer + dp
class Solution:
    def findSubstringInWraproundString(self, p: str) -> int:
        l, r = 0, 1
        dp = collections.defaultdict(int)
        while r <= len(p):
            while r < len(p) and (ord(p[r]) - ord(p[r-1]))%26 == 1:
                r += 1
            while l < r:
                dp[p[l]] = max(dp[p[l]], r- l)
                l +=1
            r+=1 
        return sum(dp.values())