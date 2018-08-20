"""
31. Next Permutation

"""

class Solution:
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        if  len(nums) <= 1:  return 
        i = len(nums)-2
        while i>=0 and nums[i] >= nums[i+1]:
            i-=1
        if i == -1: 
            nums[:] = nums[::-1]
        else:
            j = len(nums)-1
            while nums[j] <= nums[i]:
                j-=1
            nums[i], nums[j] = nums[j], nums[i]
            nums[i+1:] = nums[i+1:][::-1]


class Solution:
    def nextPermutation(self, nums):
        for i in range(len(nums)-1, -1, -1):
            if i-1 >=0 and nums[i] > nums[i-1]:
                for j in reversed(range(i,len(nums))):
                    if nums[j] > nums[i-1]:
                        nums[i-1], nums[j] = nums[j], nums[i-1]
                        break
                nums[i:] = nums[i:][::-1]
                break
        else:
            nums = nums.reverse()