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
    def minStickers(self, stickers: List[str], target: str) -> int:
        if set(target).difference(*stickers):
            return -1
        def ms(target, memo={(): 0}):
            key = tuple(sorted(target.elements()))
            if key not in memo:
                memo[key] = 1 + min(ms(target - s) for s in stickers if min(target) in s)
            return memo[key]
        stickers = list(map(collections.Counter, stickers))
        return ms(collections.Counter(target))


# It's even faster to instead use the character that occurs in the fewest stickers. Gets accepted in about 650 ms:

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        if set(target).difference(*stickers):
            return -1
        def ms(target, memo={(): 0}):
            key = tuple(sorted(target.elements()))
            if key not in memo:
                c = min(target, key=lambda c: sum(c in s for s in stickers))
                memo[key] = 1 + min(ms(target - s) for s in stickers if c in s)
            return memo[key]
        stickers = list(map(collections.Counter, stickers))
        return ms(collections.Counter(target))



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
                




from collections import Counter
from heapq import heappush, heappop
class Solution(object):
    def minStickers(self, stickers, target):
        def get_key(cnt):
            return "".join(sorted(list(cnt.elements())))

        #The first section just make the available number of stickers smaller
        #Some stickers will actually have the same results on making the target
        #Example (1), if target = 'abc', two stickers 'aef' and 'agh' are actually the same thing 
        #in terms of making the target, so we only need to reserve one sticker
        #Example (2), if target = 'abc', two stickers 'abf' and 'agh'. We only need to reserve `abf`, 
        #because whatever 'agh' can contribute, we can use 'abf' to achieve the same result,
        #or a better one. 
        target_cnt = Counter(target)
        stks_cnt = [Counter(sticker) & target_cnt for sticker in stickers]
        stks_key = [get_key(stk) for stk in stks_cnt]
        stks_key = sorted(list(set(stks_key)), key = lambda x: -len(x))
        stks_cnt = []
        for stk_key in stks_key:
            sub = False
            for cnt in stks_cnt:
                if len(Counter(stk_key) - cnt) == 0:
                    sub = True
            if not sub:
                stks_cnt.append(Counter(stk_key))
        #The result stks_cnt only contains useful stickers that never give the same results
        #in the process of making the target. In some cases, only 14 / 50 stickers remained.
        
        visited = set()
        target_key = get_key(target_cnt)
        
        #now we have a BFS to search for the minimal number of stickers
        queue = [(0, target_key)]
        visited.add(target_key)

        while queue:
            #Here, I actuall maintain a priority queue in BFS
            #I just want to get the results as early as possible, 
            #so I prioritize a new state of shorter length 
            length, cnt = heappop(queue) 
            for stk in stks_cnt:
                res = Counter(cnt) - stk
                key = get_key(res)
                if len(key) == 0:
                    return length + 1
                elif key not in visited:
                    visited.add(key)
                    heappush(queue, (length + 1, key))
        return -1