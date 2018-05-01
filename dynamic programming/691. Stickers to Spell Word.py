"""
691. Stickers to Spell Word

"""


"""
Accepted but slow
"""
import collections
class Solution:
    def minStickers(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        t_count = collections.Counter(target)
        A = [collections.Counter(sticker) & t_count
             for sticker in stickers]

        for i in range(len(A) - 1, -1, -1):
            if any(A[i] == A[i] & A[j] for j in range(len(A)) if i != j):
                A.pop(i)
        
        stickers = ["".join(s_count.elements()) for s_count in A]
        nn = 1<<len(target)
        dp = collections.defaultdict(lambda: -1)
        dp[0] = 0
        for i in range(nn):
            if i in dp:
                for key in stickers:
                    now = i
                    for m, k in enumerate(key): 
                        for j, t in enumerate(target):
                            if k != t or (now & (1<<j)): continue
                            now |= 1<<j
                            break
                        if now in dp:
                            dp[now] = min(dp[now],dp[i]+1)
                        else:
                            dp[now] = dp[i]+1
        #print(dp,nn)
        return dp[nn-1] if nn-1 in dp else -1
                    
                    


class Solution:
    def minStickers(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        num = len(stickers)
        mp = [[0] * 26 for _ in range(num)]
        for i in range(num):
            for word in stickers[i]:
                mp[i][ord(word) - ord('a')] += 1
        dp = {}
        dp[''] = 0
        
        def match(dp, mp, target):
            if target in dp:
                return dp[target]
            n = len(mp)
            tar = [0] * 26
            for word in target:
                tar[ord(word) - ord('a')] += 1
            ans = 10000
            for i in range(n):
                if mp[i][ord(target[0]) - ord('a')] == 0: continue
                s = ''
                for j in range(26):
                    if tar[j] > mp[i][j]:
                        s += chr((ord('a') + j)) * (tar[j] - mp[i][j])
                tmp = match(dp, mp, s)
                if tmp != -1:
                    ans = min(ans, tmp + 1)
            dp[target] = -1 if ans == 10000 else ans
            return dp[target]
        
        return match(dp, mp, target)
                
            