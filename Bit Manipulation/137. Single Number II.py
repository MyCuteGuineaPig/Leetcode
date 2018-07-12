"""
137. Single Number II


Example 1:

Input: [2,2,3,2]
Output: 3

Input: [0,1,0,1,0,1,99]
Output: 99
"""

class Solution:
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        one = two = 0
        for i in nums:
            one = (one ^ i) & (~two)
            two = (two ^ i) & (~one)
        return one

class Solution:
    def singleNumber(self, nums):
        one = two = mask = 0
        for i in nums:
            two = two ^ (i & one)  
            one = one ^ i   
            mask = ~(one & two)
            two = two & mask
            one = one & mask
        return one