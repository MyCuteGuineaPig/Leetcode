"""
462. Minimum Moves to Equal Array Elements II

"""


class Solution:
    def minMoves2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        i, j = 0, len(nums)-1
        res = 0
        while i<j:
            res += nums[j] - nums[i]
            j-=1
            i+=1
        return res


class Solution:
    def minMoves2(self, nums):
        median = sorted(nums)[len(nums) // 2]
        return sum(abs(num - median) for num in nums)

import functools
class Solution:
    def minMoves2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        return functools.reduce(lambda x, i: x ^ nums[i]^ nums[~i], range(len(nums)//2), 0)

