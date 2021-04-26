class Solution:
    def longestBeautifulSubstring(self, word: str) -> int:
        cnt = 1
        start = res = 0
        for i, (prev, cur) in enumerate(zip(word, word[1:]), 1):
            if cur < prev:
                cnt = 1
                start = i
            elif cur > prev:
                cnt += 1
            if cnt == 5:
                res = max(res, i - start + 1)
        return res

class Solution:
    def longestBeautifulSubstring(self, word: str) -> int:
        seen = set()
        lo, longest, cur = -1, 0, 0
        for hi, c in enumerate(word):
            if hi > 0 and c < word[hi - 1]:
                seen = set()
                lo = hi - 1    
                cur = 0
            seen.add(c)    
            if len(seen) == 5:
                longest = max(longest, hi - lo)
        return longest