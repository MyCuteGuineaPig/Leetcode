class Solution:
    def maximumTotalDamage(self, power: List[int]) -> int:
        mp = sorted(Counter(power).items())
        j = 0
        res = 0
        prev = 0
        for i, (k, v) in enumerate(mp):
            while j < i and mp[j][0] < k - 2:
                prev = max(prev, mp[j][1])
                j+=1
            mp[i] = [k, v * k + prev]
            res = max(res, mp[i][1])
        return res
