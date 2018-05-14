"""
35. Search Insert Position
"""
class Solution:
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        l, r = 0, len(nums)-1
        if r >= 0 and target>nums[-1]: return r+1
        elif r<0 or (r == 0 and target<nums[0]): return 0
        while l<r:
            mid = (l+r)>>1
            if nums[mid] >= target: r = mid
            else: l = mid+1
        return l

class Solution:
    def searchInsert(self, nums, target):
        l, r = 0, len(nums)
        while l<r:
            mid = (l+r)>>1
            if nums[mid] >= target: r = mid
            else: l = mid+1
        return l
    

class Solution:
    def searchInsert(self, nums, target):
        return bisect.bisect_left(nums,target)
    


class Solution:
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        start=0
        end=len(nums)-1
        
        while(start<=end):
            mid=(start+end)//2
            if nums[mid]==target:
                return mid
            elif nums[mid]<target:
                start=mid+1
            else:
                end=mid-1
        return end+1 # or return start