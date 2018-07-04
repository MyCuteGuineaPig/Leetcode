"""
1. Two Sum

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
"""

class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        dic = collections.defaultdict(int)
        for i, v in enumerate(nums):
            if target - v in dic: 
                return [dic[target-v], i]
            dic[v] = i