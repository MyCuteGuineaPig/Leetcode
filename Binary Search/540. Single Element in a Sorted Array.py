"""
540. Single Element in a Sorted Array

Example 1:
Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:
Input: [3,3,7,7,10,11,11]
Output: 10


"""
class Solution(object):
    def singleNonDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l,r = 0, len(nums)-1
        while l < r:
            mid = (l+r)>>1
            if mid&1:
                mid -= 1
            if nums[mid]!= nums[mid+1]:
                r = mid
            else:
                l = mid+2
        return nums[l]