"""
283. Move Zeroes

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
"""

class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        c = 0
        for i,v in enumerate(nums):
            if v != 0:
                nums[c], nums[i] = nums[i], nums[c]
                c+=1
        

 class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        i = 0
        for num in nums:
            if num != 0:
                nums[i] = num
                i += 1
        while i < len(nums):
            nums[i] = 0
            i += 1               