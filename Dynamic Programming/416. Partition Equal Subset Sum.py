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

class Solution:
    def canPartition(self, nums):
        if sum(nums) & 1 == 0:
            target = sum(nums) >> 1
            cur = {0}
            for i in nums:
                cur |= {i + x for x in cur}
                if target in cur:
                    return True
        return False


class Solution:
    def canPartition(self, nums):
        return (sum(nums) / 2.) in reduce(lambda cur, x: cur | {v + x for v in cur}, nums, {0})



class Solution:
    def canPartition(self, nums):
        total = sum(nums)
        if total % 2 == 1: return False
            
        target = total / 2   #target sum 
        s = set([0])         #stores the sums of the subsets
        
        for n in nums:
            sums_with_n = []  #stores the sums of the subsets that contain n
            for i in s:
                if i + n == target: return True
                if i + n < target:
                    sums_with_n.append(i + n)
            s.update(sums_with_n)
                
        return False