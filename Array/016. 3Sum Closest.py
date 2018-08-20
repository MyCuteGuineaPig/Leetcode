"""
16. 3Sum Closest

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

"""

class Solution:
    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()

        if nums[0] + nums[1] + nums[2] > target:
            return nums[0] + nums[1] + nums[2]
        if nums[-1] + nums[-2] + nums[-3] < target:
            return nums[-1] + nums[-2] + nums[-3]

        res = sum(nums[:3])
        for ind, val in enumerate(nums[:-2]):
            if ind > 0 and nums[ind-1] == val: continue
            i, j = ind + 1, len(nums)-1
            while i< j: 
                temp = val + nums[i] +nums[j]
                if abs(temp-target) < abs(res - target):
                    res = temp
                if temp  == target: return target
                elif temp < target: 
                    while i + 1 < j and nums[i+1] == nums[i]: i+=1
                    i+=1
                else:
                    while i < j - 1 and nums[j-1] == nums[j]: j-=1
                    j-=1
        return res



class Solution:
    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        if len(nums) == 3:
            return sum(nums)
        
        nums = sorted(nums)
        
        if nums[0] + nums[1] + nums[2] > target:
            return nums[0] + nums[1] + nums[2]
        if nums[-1] + nums[-2] + nums[-3] < target:
            return nums[-1] + nums[-2] + nums[-3]
        
        best = float('inf')
        max_index = len(nums) - 2
        result = []
        
        for i in range(len(nums) - 2):
            s, e = i + 1, len(nums) - 1
            if nums[i] + nums[e] + nums[e-1] < target:  #最大的都比target小, 不用继续了
                result.append(nums[i] + nums[e] + nums[e-1])
                continue
            if nums[i] + nums[s] + nums[s+1] > target: #最小的都比target大, 不用继续了
                result.append(nums[i] + nums[s] + nums[s+1])
            else:
                while s < e and s <= max_index:
                    r = nums[i] + nums[s] + nums[e]
                    result.append(r)

                    if r > target:
                        e -= 1
                    elif r < target:
                        s += 1
                    else:
                        return target
                
            max_index = s
            
        result = sorted(result, key=lambda x: abs(x - target))
                    
        return result[0]