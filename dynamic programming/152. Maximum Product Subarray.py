"""
152. Maximum Product Subarray
"""

class Solution:
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        localmin = nums[0]
        globalmax = localmax = nums[0]
        for i in nums[1:]:
            localmin, localmax = min(i,i*localmax,i*localmin), max(i, localmax*i,localmin*i)
            globalmax = max(globalmax, localmax)
        return globalmax

class Solution:
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        localmin = nums[0]
        globalmax = localmax = nums[0]
        for i in nums[1:]:
            if i < 0:
                localmin, localmax = localmax, localmin
            localmin =  min(i,i*localmin)
            localmax =  max(i, localmax*i)
            globalmax = max(globalmax, localmax)
        return globalmax