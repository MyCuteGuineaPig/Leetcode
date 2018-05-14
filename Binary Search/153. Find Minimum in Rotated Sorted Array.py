"""
153. Find Minimum in Rotated Sorted Array
"""

class Solution:
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l, r = 0, len(nums)-1
        while l<r:
            mid = (l+r)>>1
            if nums[mid]<nums[l] or nums[mid]<nums[r]: #nums[mid]<nums[l] turn on left, or no turn from left to right
                r = mid
            else:
                l = mid+1
        return nums[l]


class Solution:
    def findMin(self, nums):
        self.__getitem__ = lambda i: nums[i] <= nums[-1]
        return nums[bisect.bisect(self, False, 0, len(nums))]