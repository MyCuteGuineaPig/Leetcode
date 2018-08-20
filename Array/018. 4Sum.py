"""
18. 4Sum


Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

"""

class Solution:
    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        nums.sort()
        res = []
        for ind, v1 in enumerate(nums[:-3]):
            if v1*4 > target: break
            if ind > 0 and nums[ind-1] == v1: continue
            for ind2, v2 in enumerate(nums[ind+1:-2],ind+1):
                if v1 + v2*3 > target: break
                if ind2 > ind + 1 and nums[ind2-1] == v2: continue
                i, j = ind2 + 1, len(nums)-1
                while i < j: 
                    tmp = v1 + v2 + nums[i] + nums[j]
                    if tmp == target:
                        res.append([v1, v2, nums[i], nums[j]])
                        while i + 1 < j and nums[i+1] == nums[i]:i+=1
                        while i < j - 1 and nums[j-1] == nums[j]: j-=1 
                        i+=1; j-=1
                    elif tmp <target: 
                        i+=1
                    else: 
                        j-=1
        return res 

#backtrack
class Solution:
    def fourSum(self, nums, target):
        def findNsum(nums, target, N, result, results):
            if len(nums) < N or N < 2 or target < nums[0]*N or target > nums[-1]*N:  # early termination
                return
            if N == 2: # two pointers solve sorted 2-sum problem
                l,r = 0,len(nums)-1
                while l < r:
                    s = nums[l] + nums[r]
                    if s == target:
                        results.append(result + [nums[l], nums[r]])
                        l += 1
                        while l < r and nums[l] == nums[l-1]:
                            l += 1
                    elif s < target:
                        l += 1
                    else:
                        r -= 1
            else: # recursively reduce N
                for i in range(len(nums)-N+1):
                    if i == 0 or (i > 0 and nums[i-1] != nums[i]):
                        findNsum(nums[i+1:], target-nums[i], N-1, result+[nums[i]], results)

        results = []
        findNsum(sorted(nums), target, 4, [], results)
        return result

#把4 sum 变成两个two sum
class Solution:
    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        nums = sorted(nums)
        hash = {}
        res = set()
        for i in range(len(nums)):
            for j in range(i+1, len(nums)):
                if nums[i] + nums[j] not in hash:
                    hash[nums[i] + nums[j]] = [(i,j)]
                else:
                    hash[nums[i] + nums[j]].append((i,j))
        for i in range(len(nums)):
            for j in range(i+1, len(nums)-2):
                if target - nums[i] - nums[j] in hash:
                    for k in hash[target - nums[i] - nums[j]]:
                        if k[0] > j:
                            res.add((nums[i], nums[j], nums[k[0]], nums[k[1]]))
        return [list(i) for i in res]