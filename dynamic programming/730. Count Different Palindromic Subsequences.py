"""
730. Count Different Palindromic Subsequences
"""

class Solution:
    def deleteAndEarn(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 0: return 0
        dic = sorted(collections.Counter(nums).items())
        take, skip = dic[0][1]*dic[0][0], 0
        for index,(k,c),  in enumerate(dic[1:]): #index从0开始数
            if dic[index][0] == k-1:
                take, skip = max(skip+c*k, take), take
            else:
                 take, skip = take+c*k, take
        return take