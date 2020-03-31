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
