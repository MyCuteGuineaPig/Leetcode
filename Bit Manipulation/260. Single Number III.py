"""
260. Single Number III


Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice.
Find the two elements that appear only once.

Input:  [1,2,1,3,2,5]
Output: [3,5]
"""
import functools
class Solution:
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = functools.reduce(operator.xor,nums)
        n &= (-n)
        res = [0, 0]
        return functools.reduce(lambda x, y: [x[0]^y, x[1]]  if y & n else [x[0], x[1]^y], nums, [0,0]
        
class Solution:
    # @param {integer[]} nums
    # @return {integer[]}
    def singleNumber(self, nums):
        x_xor_y = reduce(operator.xor, nums)
        bit =  x_xor_y & -x_xor_y
        result = [0, 0]
        for i in nums:
            result[bool(i & bit)] ^= i
        return result