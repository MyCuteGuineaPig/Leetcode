"""
312. Burst Balloons
"""

class Solution:
    def maxCoins(self, nums):
        dp = [[0 for _ in range(len(nums)+2)] for _ in range(len(nums)+2)]
        for k in range(2,len(nums)+2):
            for left in range(0,len(nums)+2-k):
                right = left + k
                for i in range(left+1, right):
                    leftnum = 1 if left == 0 else nums[left-1]
                    rightnum = 1 if right == len(nums)+1 else nums[right-1]
                    dp[left][right] = max(dp[left][right], dp[left][i] + dp[i][right] + leftnum*rightnum*nums[i-1])
        return dp[0][-1]

class Solution:
    def maxCoins(self, nums):
        nums = [1] + nums +[1]
        dp = [[0 for _ in range(len(nums))] for _ in range(len(nums))]
        for k in range(2,len(nums)):
            for left in range(0,len(nums)-k):
                right = left + k
                for i in range(left+1, right):
                    dp[left][right] = max(dp[left][right], dp[left][i] + dp[i][right] + nums[left]*nums[right]*nums[i])
        return dp[0][-1]


class Solution:
    def maxCoins(self, nums):
        nums = [1] + nums +[1]
        dp = [[0 for _ in range(len(nums))] for _ in range(len(nums))]
        for k in range(2,len(nums)):
            for left in range(0,len(nums)-k):
                right = left + k
                for i in range(left+1, right):
                    dp[left][right] = max(dp[left][right], dp[left][i] + dp[i][right] + nums[left]*nums[right]*nums[i])
        return dp[0][-1]


class Solution:
    def maxCoins(self, nums):
        nums = [1] + nums +[1]
        dp = [[0 for _ in range(len(nums))] for _ in range(len(nums))]
        for k in range(2,len(nums)):
            for left in range(0,len(nums)-k):
                right = left + k
                dp[left][right] = max((dp[left][i] + dp[i][right] + nums[left]*nums[right]*nums[i] for i in range(left+1, right)), default=0)
        return dp[0][-1]


#2020
class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        n = len(nums)
        if not n:
            return 0
        dp = [[0 for _ in range(n)] for _ in range(n)]
        for k in range(1,n+1): 
            for i in range(n):
                for j in range(k):
                    start = i - j if i - j >= 0 else 0
                    end = i + k - j - 1 if i + k - j - 1 < n else n-1
                    
                    left = nums[start-1] if start - 1 >= 0 else 1
                    midleft = dp[start][i-1] if start >= 0 and start <= i-1 else 0
                    right = nums[end+1] if end + 1 < n else 1
                    midright  = dp[i+1][end] if end < n and end >= i + 1 else 0 
                    
                    dp[start][end] = max(dp[start][end], midleft + left * nums[i]*right + midright)

        return dp[0][n-1]

# 2020 
class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        n = len(nums)
        if not n:
            return 0
        dp = [[0 for _ in range(n)] for _ in range(n)]

        for k in range(1,n+1): 
            for left in range(0, n-k+1):
                right = left + k-1
                for i in range(left, right+1):
                    leftnum = rightnum = 1
                    if left != 0: leftnum = nums[left-1]
                    if right != n-1: rightnum = nums[right+1]
                        
                    dp[left][right] = max(dp[left][right], leftnum*rightnum*nums[i] + (dp[left][i-1] if i - 1 >= left else 0) + (dp[i+1][right] if right >= i+1 else 0))
     
        return dp[0][n-1]