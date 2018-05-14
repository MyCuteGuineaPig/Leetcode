"""
81. Search in Rotated Sorted Array II
"""
class Solution:
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: bool
        """
        l, r, n = 0, len(nums)-1, len(nums)
        while l<=r:
            while r>l and nums[l+1]==nums[l]:
                l+=1
            while r>l and nums[r-1] == nums[r]:
                r-=1
            mid = (l+r)>>1
            if nums[mid] == target: return True
            if target > nums[mid]:
                if nums[l]>nums[mid] and nums[l]<=target: r = mid-1
                else: l = mid+1
            else:
                if nums[mid]>nums[r] and nums[r]>=target: l = mid+1
                else: r = mid-1   
            
        return False
