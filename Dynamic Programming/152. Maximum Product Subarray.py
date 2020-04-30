"""
152. Maximum Product Subarray
"""

class Solution:
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        localmin = nums[0]
        globalmax = localmax = nums[0]
        for i in nums[1:]:
            localmin, localmax = min(i,i*localmax,i*localmin), max(i, localmax*i,localmin*i)
            globalmax = max(globalmax, localmax)
        return globalmax

class Solution:
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        localmin = nums[0]
        globalmax = localmax = nums[0]
        for i in nums[1:]:
            if i < 0:
                localmin, localmax = localmax, localmin
            localmin =  min(i,i*localmin)
            localmax =  max(i, localmax*i)
            globalmax = max(globalmax, localmax)
        return globalmax


"""
Calculate prefix product in A.
Calculate suffix product in A.
Return the max.
"""

class Solution:
    def maxProduct(self, A):
        B = A[::-1]
        for i in range(1, len(A)):
            A[i] *= A[i - 1] or 1
            B[i] *= B[i - 1] or 1
        return max(A + B)