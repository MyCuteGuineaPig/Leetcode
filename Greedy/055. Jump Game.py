"""
55. Jump Game

Example 1:

Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.

"""

class Solution:
    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        end = 0; far = 0
        for i, v in enumerate(nums[:-1]):
            far = max(far, i+v)
            if end == i: 
                if v == 0 and far == i: 
                    return False
                end = far
        return True


class Solution:
    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        if len(nums)<=1: return True
        step = nums[0]
        for v in nums:
            step -=1
            if step < 0: 
                return False
            step = max(step, v)
        return True


class Solution:
    def canJump(self, nums):
        width = 0#从最后过来, 差几个距离，没有补上
        for i in reversed(nums[:-1]):
            if width >= i:width+=1
            else: width = 0
        return not width


class Solution:
    def canJump(self, nums):
        goal = len(nums)-1
        for i in reversed(range(len(nums)-1)):
            if i+nums[i] >= goal: 
                goal = i
        return not goal