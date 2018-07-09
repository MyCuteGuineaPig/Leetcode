"""

561. Array Partition I

Given an array of 2n integers, your task is to group these integers into n pairs of integer, 
say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.


Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).

"""

class Solution:
    def arrayPairSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        li = [0]*20001
        for i in nums:
            li[i+10000]+=1
        r = res = 0
        for i, v in enumerate(li):
            res += (v - r +  1)//2*(i-10000) # 4 // 2 = 
            r = (v + r) % 2
        return res

class Solution:
    def arrayPairSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        
        return sum((sorted(nums))[::2])