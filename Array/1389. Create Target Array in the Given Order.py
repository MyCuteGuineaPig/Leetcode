class Solution:
    def createTargetArray(self, nums: List[int], index: List[int]) -> List[int]:
        l = []
        for v, i in zip(nums, index):
            l.insert(i,v)
        return l

class Solution:
    def createTargetArray(self, nums: List[int], index: List[int]) -> List[int]:
        for i in range(len(nums)):
            for j in range(i):
                if index[j] >= index[i]:
                    index[j] += 1
        result = [0]*(len(nums))
        for i in range(len(nums)):
            result[index[i]] = nums[i]
        return result

import itertools
class Solution(object):
    def createTargetArray(self, nums, index):
        """
        :type nums: List[int]
        :type index: List[int]
        :rtype: List[int]
        """
        result = []
        for i, x in itertools.izip(index, nums):
            result.insert(i, x)
        return result


