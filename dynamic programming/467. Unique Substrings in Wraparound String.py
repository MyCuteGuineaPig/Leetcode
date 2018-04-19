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


import collections
class Solution:
    def findSubstringInWraproundString(self, p):
        """
        :type p: str
        :rtype: int
        """
        if len(p)==0 : return 0
        letters, length,res = collections.defaultdict(int), 1, 1
        set_ = set(['ab','bc','cd','de','ef','fg','gh','hi','ij','jk','kl','lm','mn','no','op','pq','qr','rs','st','tu','uv','vw','wx','xy','yz','za'])
        letters[p[0]] = 1
        for i in range(1,len(p)):
            if p[i-1]+p[i] not in set_:
                length = 0
            length += 1 
            if letters[p[i]] < length :
                letters[p[i]], res = length, res + length - letters[p[i]]
        return res
