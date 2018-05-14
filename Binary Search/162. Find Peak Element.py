"""
162. Find Peak Element
Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 
"""
class Solution:
    def findPeakElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l, r = 0, len(nums)-1
        while l<r:
            mid = (l+r)>>1
            #print(l,r,mid)
            if nums[mid]>=nums[l] and nums[mid+1]>nums[mid]: 
                #nums[mid]>=nums[l] 是避免mid = l,就不加了, 比如[4,5], l =0, r = 1, mid =0, 
                l = mid+1
            else:
                r = mid  
        return l
        

class Solution:
    def findPeakElement(self, nums):
        start, end = 0, len(nums) - 1
        while start < end:
            mid = start + (end - start) // 2
            if nums[mid] > nums[mid+1]:
                end = mid
            else:
                start = mid + 1
        return start