"""
Track List[1] until it get back to position 1

mp key next index, value is current index
"""
class Solution:
    def reinitializePermutation(self, n: int) -> int:
        if n <= 2:
            return 1
        mp = {}
        for i in range(n):
            if i & 1:
                mp[n//2 + (i-1)//2] = i
            else:
                mp[i//2] = i
                

        def find(i):
            if i == 1:
                return 0
            return 1 + find(mp[i])
        return 1+find(2)



class Solution:
    def reinitializePermutation(self, n: int) -> int:
        res, i = 0, 1
        while res == 0 or i > 1:
            if i < n / 2:
                i *= 2
            else:
                i = (i - n / 2) * 2 + 1
            res += 1
        return res