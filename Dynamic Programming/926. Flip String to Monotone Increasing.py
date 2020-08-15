"""
we just need to find the i in the initial string. We make all 1 before index i flip to 0, and make all 0 after index i flip to 1. 
"""

class Solution(object):
    def minFlipsMonoIncr(self, s):
        n = len(s)
        cnt0 = s.count('0')
        cnt1 = 0
        res = n - cnt0
        for i in range(n):
            if s[i] == '0': 
                cnt0 -= 1
            elif s[i] == '1':
                res = min(res, cnt1+cnt0) #后面还剩的0翻过来，加上之前翻过的1
                cnt1 += 1
        return res


class Solution:
    def minFlipsMonoIncr(self, s, ones = 0):
        res = zeros = s.count("0")
        for c in s:
            ones, zeros = (ones + 1, zeros) if c == "1" else (ones, zeros - 1)
            res = min(res, ones + zeros)
        return res


class Solution:
    def minFlipsMonoIncr(self, S: str) -> int:
        dp0, dp1 = 0, 0 # dp0: maintain a all-0 array; dp1: maintain an array that end with 1
        for c in S:
            if c == '0':
                dp0, dp1 = dp0, dp1 + 1 #i-1是0，i是0，step不变,  //i-1是1，i是0，所以step + 1
            else:
                dp0, dp1 = dp0 + 1, min(dp0, dp1) # i-1 是0, i 是1，step + 1; i 是 0， 若i-1 是1, step 不变;  若i-1是0，step + 1
        return min(dp0, dp1)