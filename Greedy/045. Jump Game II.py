"""
45. Jump Game II


Example:

Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
"""


class Solution:
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n<2: return 0
        step, reach, next = 0, 0, 0
        for i, v in enumerate(nums):
            if i == reach: 
                reach = max(next, i+v)
                step += 1
                if reach >= n-1: break
                next = nums[reach] + reach
            else:
                next = max(next, i+v)
        return step



class Solution:
    def jump(self, nums):
        n = len(nums)
        step, end, next = 0, 0, 0
        for i, v in enumerate(nums[:-1]):
            next = max(next, i + v)
            if i == end:
                step += 1
                end = next
        return step


class Solution:
    # @param {integer[]} nums
    # @return {integer}
    def jump(self, nums):
        n, start, end, step = len(nums), 0, 0, 0
        while end < n - 1:
            step += 1
            maxend = end + 1
            for i in range(start, end + 1):
                if i + nums[i] >= n - 1:
                    return step
                maxend = max(maxend, i + nums[i])
            start, end = end + 1, maxend
        return step


class Solution:
    # @param {integer[]} nums
    # @return {integer}
    def jump(self, nums):
        n, cur_max, next_max, steps = len(nums), 0, 0, 0
        for i in range(n):
            if i>cur_max:
                steps+=1
                cur_max=next_max
                if cur_max>=n:break
            next_max=max(next_max,nums[i]+i)
        return steps