class Solution:
    def countStableSubarrays(self, capacity: List[int]) -> int:
        count = defaultdict(Counter)
        res = pre = 0
        for i, a in enumerate(capacity):
            res += count[a][pre - a]
            pre += a
            count[a][pre] += 1
            if a == 0 and i > 0 and capacity[i - 1] == 0:
                res -= 1
        return res