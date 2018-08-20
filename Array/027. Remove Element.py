"""
27. Remove Element


Example 1:

Given nums = [3,2,2,3], val = 3,

Your function should return length = 2, with the first two elements of nums being 2.

It doesn't matter what you leave beyond the returned length.
Example 2:

Given nums = [0,1,2,2,3,0,4,2], val = 2,

Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.

Note that the order of those five elements can be arbitrary.

It doesn't matter what values are set beyond the returned length.

"""

class Solution:
    def removeElement(self, nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """
        j = 0
        for i, v in enumerate(nums):
            if v != val:
                nums[j] = v
                j+=1
        return j


class Solution:
    def removeElement(self, nums, val):
        l, r = 0, len(nums)
        while l < r: 
            if nums[l]!=val: l+=1
            else: 
                r -= 1
                nums[l], nums[r] = nums[r], nums[l]
        return r