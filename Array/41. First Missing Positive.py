"""
41. First Missing Positive


Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
"""

class Solution:
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i = 0
        while i < len(nums):
            if nums[i] > 0 and nums[i] <= len(nums): 
                ind = nums[i] - 1 
                if nums[ind]!= nums[i]: 
                    nums[ind], nums[i] = nums[i], nums[ind]
                else:
                    i+=1
            else:
                i+=1
        #print(nums)
        for i, v in enumerate(nums): 
            if v != i+1: 
                return i+1
        return len(nums)+1


class Solution:
    def firstMissingPositive(self, nums):
        start, end = 0, len(nums)-1
        while start <= end: 
            ind = nums[start] - 1 
            if start == ind: start += 1
            elif ind <0 or ind > end or nums[ind] == nums[start]:
                nums[start] = nums[end]
                end -=1
            else:
                nums[start], nums[ind] = nums[ind], nums[start]
        return start + 1