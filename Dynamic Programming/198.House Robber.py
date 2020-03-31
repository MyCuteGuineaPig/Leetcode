"""
198	House Robber
"""


class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        now, last = 0, 0 
        for n in nums: 
            last, now = now, max(n+last, now)
        return now 


class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)==0 : return 0
        p1, p2, p = 0, 0, nums[0]
        for n in nums[1:]: 
            p1, p2 = p, p1
            p = max(n+p2,p1)
        return p 