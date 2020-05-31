"""
377. Combination Sum IV
"""

class Solution:
    def combinationSum4(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()
        dp = [0 for _ in range(target+1)]
        for i in range(1,target+1):
            for n in nums:
                if n>i:
                    break
                if n == i:
                    dp[i] += 1
                else:
                    dp[i] += dp[i-n]
        return dp[target]

#bottom-up
class Solution:
    def combinationSum4(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()
        dp = [0]*(target + 1)
        dp[0] = 1
        for i in range(1, target+1):
            for num in nums:
                if num>i:
                    break
                dp[i]+=dp[i-num]
        return dp[target]
    

#bottom-up
class Solution:
    def combinationSum4(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        cache = {}
        def f(val):
          print(" in ",val)
          if val == target:
            return 1

          total = 0
          remain = target - val
          for num in nums:
            if num <= remain:
              k = val+num
              if k in cache:
                total += cache[k]
              else:
                cache[k] = f(val + num)
                total += cache[k]
          return total
        
        return f(0)

#2020 Top-Down
class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        dp = [1] + [-1 for _ in range(target)]
        def topDown(target):
            if dp[target] >= 0:
                return dp[target]
            cur = 0
            for i in nums:
                if i <= target:
                    cur += topDown(target-i)
            dp[target] = cur
            return dp[target]
        return topDown(target)