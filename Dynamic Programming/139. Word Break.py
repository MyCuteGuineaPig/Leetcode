"""
139. Word Break
"""
class Solution:
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        dict_ = set(wordDict)
        dp = [False for _ in range(len(s)+1)]
        dp[0] = True
        for i in range(len(s)):
            for j in range(i,-1,-1):
                if dp[i+1]: 
                    break
                if s[j:i+1] in dict_: 
                    dp[i+1] = dp[j]
        return dp[-1] 
        

import functools
class Solution:
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        @functools.lru_cache(maxsize=None) // 需要它否则timeout
        def can_decode(i):
            if i == len(s):
                return True
            for w in wordDict:
                if s.startswith(w, i) and can_decode(i + len(w)):
                    return True
            return False

        return can_decode(0)




class Solution:
    def wordBreak(self, s, words):
        ok = [True]
        for i in range(1, len(s)+1):
            ok += any(ok[j] and s[j:i] in words for j in range(i)),
        return ok[-1]



#Suffix Trie + DP
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        trie = {}
        for word in wordDict:
            t = trie 
            for w in word:
                t = t.setdefault(w,{})
            t['#'] = '#' 

        F = [1] + [0,]*len(s)
        s = list(s)
        for i, v in enumerate(s):
            if F[i]:
                t = trie
                j = i
                while j < len(s) and s[j] in t:
                    t = t[s[j]]
                    if '#' in t:
                        F[j+1] = True 
                        if j == len(s)-1:
                            return True
                    j += 1
        return F[len(s)]

