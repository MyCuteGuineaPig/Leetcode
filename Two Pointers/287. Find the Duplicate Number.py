"""
287. Find the Duplicate Number

Example 1:

Input: [1,3,4,2,2]
Output: 2
Example 2:

Input: [3,1,3,4,2]
Output: 3
"""

class Solution(object):
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)-1
        i , j = nums[0], nums[nums[0]] #slow往前进一位,fast往前进两位保持一致，这样第一个while 不会停住
        while i!=j:  
            i,j = nums[i], nums[nums[j]]
        j = 0
        while i!=j:
            i,j = nums[i], nums[j]
        return i

class Solution(object):
    def findDuplicate(self, nums):
        n = len(nums)-1
        i , j = 0, 0
        while i==0 or i!=j:  
            i,j = nums[i], nums[nums[j]]
        j = 0
        while i!=j:
            i,j = nums[i], nums[j]
        return i

class Solution(object):
    def findDuplicate(self, nums):
        n = len(nums)-1
        i , j = n, n
        while i == n or i!=j:  
            i, j = nums[i]-1, nums[nums[j]-1]-1
        j = n
        while i!=j:
            i, j = nums[i]-1, nums[j]-1
        return i+1



#binary search
class Solution(object):
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l, r = 0, len(nums)-1
        while l<r:
            mid = (l+r)>>1
            count = 0
            for i in nums:
                if i<=mid:
                    count+=1
            #print(count, mid, l, r)
            if count<=mid:
                l=mid+1
            else:
                r=mid
        return l