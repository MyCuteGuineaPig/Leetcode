"""
376. Wiggle Subsequence

Example 1:

Input: [1,7,4,9,2,5]
Output: 6
Example 2:

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
Example 3:

Input: [1,2,3,4,5,6,7,8,9]
Output: 2

"""

class Solution:
    def wiggleMaxLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)<=1: return len(nums)
        cnt = ind = 1
        while ind < len(nums) and nums[ind] == nums[ind-1]:  #跳过重复的
            ind += 1 
        if ind < len(nums):
            sign = nums[ind] - nums[ind-1] # positive: true, negative: false
            cnt += 1
        for i, pre in zip(nums[ind+1:], nums[ind:-1]):
            if (i - pre)*sign < 0: 
                sign = (i - pre)
                cnt += 1
        return cnt


class Solution:
    def wiggleMaxLength(self, nums):
        if len(nums)<=1: return len(nums)
        cnt = 1; sign  = 0
        for i, prev in zip(nums[1:], nums[:-1]):
            if i > prev and (sign == 0 or sign == -1): 
                cnt += 1
                sign = 1 
            elif i < prev and (sign == 0 or sign == 1):
                cnt += 1 
                sign = -1
        return cnt


class Solution:
    def wiggleMaxLength(self, nums):
        if len(nums)<=1: return len(nums)
        down = up = 1
        for i, prev in zip(nums[1:], nums[:-1]):
            if i > prev: up = down +1 
            elif i < prev: down = up +1 
        return max(up, down)

class Solution:
    def wiggleMaxLength(self, nums):
        nan = float('nan')
        diffs = [a-b for a, b in zip([nan] + nums, nums + [nan]) if a-b]
        return sum(not d*e >= 0 for d, e in zip(diffs, diffs[1:]))
        """
        [1,7,4,9,2,5]
        diffs = [nan, -6, 3, -5, 7, -3, nan]
        nan * 1 >= 0 false, nan*1 <= 0 也是false
        zip(diffs, diffs[1:]):  [(nan, -6), (-6, 3), (3, -5), (-5, 7), (7, -3), (-3, nan)]

        比如: [1,1,1,1,1,1]
        diffs = [nan, nan]
        """
        

 class Solution:   
    def wiggleMaxLength(self, nums):
        norep = [num for num, _ in itertools.groupby(nums)]
        triples = zip(norep, norep[1:], norep[2:])
        return sum((b>a) == (b>c) for a, b, c in triples) + len(norep[:2])
        """
        [1,7,7,4,7,9,2,5]: 
        norep = [1, 7, 4, 7, 9, 2, 5]
        triples = [(1, 7, 4), (7, 4, 7), (4, 7, 9), (7, 9, 2), (9, 2, 5)]
        """

class Solution:
    def wiggleMaxLength(self, nums):
        norep = [num for num, _ in itertools.groupby(nums)]
        if len(norep) < 2: return len(norep)
        triples = zip(norep, norep[1:], norep[2:])
        return 2 + sum(a<b>c or a>b<c for a, b, c in triples)