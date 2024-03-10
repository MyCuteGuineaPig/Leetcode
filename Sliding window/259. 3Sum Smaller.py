class Solution:
    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        nums.sort()
        n = len(nums)
        res = 0
        for i in range(n):
            if nums[i] * 3 >= target:
                break
            j = i+ 1
            k = n-1
            while j < k:
                if nums[i] + nums[j] + nums[k] < target:
                    res += k - j
                    j+=1
                else:
                    k -= 1
            
        return res

import bisect
class Solution:
    def threeSumSmaller(self, nums, target):
        nums.sort()
        count = 0
        for k in range(len(nums)):
            i, j = 0, k - 1
            while i < j:
                if nums[i] + nums[j] + nums[k] < target:
                    count += j - i
                    i += 1
                else:
                    j -= 1
        return count