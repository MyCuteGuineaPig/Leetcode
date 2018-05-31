"""
75. Sort Colors
Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
"""


"""
Count Sort
complexity:  O(n)
Space: O(1)
"""

class Solution:
    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        n0, n1, n2 = -1,-1,-1
        for i in nums:
            if i == 0: 
                n2 += 1; n1+=1 ; n0+=1
                nums[n2] = 2; nums[n1] = 1; nums[n0] = 0
            elif i == 1:
                n2+=1 ; n1+=1
                nums[n2] = 2; nums[n1] = 1
            else: 
                n2 += 1
                nums[n2] = 2

"""
Inplace swap: 把2弄到后面去
// Tri-Partition solution.
"""
class Solution:
    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        c0, c2 = 0, len(nums)-1
        i = 0
        while i<=c2:
            if nums[i] == 0:
                nums[i], nums[c0] = nums[c0], nums[i]
                c0+=1
                i+=1
            elif nums[i] == 2:
                nums[i], nums[c2] = nums[c2], nums[i]
                c2 -=1
            else: i+=1
        