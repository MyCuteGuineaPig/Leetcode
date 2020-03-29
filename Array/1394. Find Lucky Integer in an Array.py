class Solution:
    def findLucky(self, arr: List[int]) -> int:
        c = collections.Counter(arr)
        res = -1
        for i, v in c.items():
            if i == v:
                res = max(res, i)
        if res != -1:
            return res
        return -1