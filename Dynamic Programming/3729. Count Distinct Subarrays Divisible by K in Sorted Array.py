class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        count = Counter([0])
        res = pre = 0
        for a in nums:
            pre = (pre + a) % k
            res += count[pre]
            count[pre] += 1
        for a, it in groupby(nums):
            tmp =  list(it)
            l = len(tmp)
            for ll in range(1, l):
                if ll * a % k == 0:
                    res -= l - ll
        return res