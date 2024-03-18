class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        tot = 0
        dic = collections.Counter({0: 1})
        res = 0
        for v in nums:
            tot += v
            res += dic[tot-goal]
            dic[tot] += 1 
        return res
