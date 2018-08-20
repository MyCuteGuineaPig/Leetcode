"""
26. Remove Duplicates from Sorted Array


Example 1:

Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.
Example 2:

Given nums = [0,0,1,1,1,2,2,3,3,4],

Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.

It doesn't matter what values are set beyond the returned length.

"""


class Solution:
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums: return 0
        i, j = 0, 1
        for j, v in enumerate(nums[1:],1):
            if v == nums[i]: continue
            else: 
                i+=1
                nums[i] = v
        return i+1

class Solution:
    def removeDuplicates(self, n):
        n[:] = sorted(list(set(n)))
        return len(n)

class Solution:
    def removeDuplicates(self, nums):
        i = 0
        for n in nums:
            if not i or n > nums[i-1]:
                nums[i] = n
                i+=1
        return i