"""
154. Find Minimum in Rotated Sorted Array II
"""
class Solution:
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l, r = 0, len(nums)-1
        while l<r:
            while l<r and nums[l+1] == nums[l]: l+=1
            while l<r and nums[r-1] == nums[r]: r-=1
            if l<r:
                mid = (l+r)>>1
                if nums[mid]<nums[l] or nums[mid]<nums[r]: #nums[mid]<nums[l] turn on left, or no turn from left to right
                    r = mid
                else:
                    l = mid+1
        return nums[l]