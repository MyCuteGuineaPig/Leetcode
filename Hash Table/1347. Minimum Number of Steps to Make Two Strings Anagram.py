class Solution:
    def minSteps(self, s: str, t: str) -> int:
        count = collections.Counter(s)
        res = 0
        for c in t:
            if count[c] > 0:
                count[c] -= 1
            else:
                res += 1
        return res

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt = 0
        c1 = collections.Counter(s)
        c2 = collections.Counter(t)
        for i in range(26):
            c = chr(ord('a') + i)
            cnt += abs(c1[c]- c2[c])  # cnt is  steps convert from s to t + steps convert t to s.
        return cnt//2
