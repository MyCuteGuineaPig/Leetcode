"""
416. Partition Equal Subset Sum

"""
class Solution:
    def canPartition(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def dfs(beg,target): 
            if target == 0:
                return True
            for i in range(beg, len(nums)):
                if target >= nums[i]:
                    if dfs(i+1, target - nums[i]): 
                        return True
                else: break
            return False
        s = sum(nums)
        if s & 1: 
            return False
        s = s >> 1
        nums.sort(reverse = True)
        return dfs(0,s)