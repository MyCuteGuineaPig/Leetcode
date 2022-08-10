class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        nums_len = len(nums)
        count_dict = dict()
        for i in range(nums_len):
            nums[i] -= i
            if nums[i] not in count_dict:
                count_dict[nums[i]] = 0
            count_dict[nums[i]] += 1
        
        count = 0
        for key in count_dict:
            count += math.comb(count_dict[key], 2)
        return math.comb(nums_len, 2) - count


class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        tot = len(nums) * (len(nums) - 1) // 2
        good = 0
        dp = {}
        
        for i,num in enumerate(nums):
            v = i - num
            good += dp.get(v, 0)
            dp[v] = dp.get(v, 0) + 1
        
        return tot - good        