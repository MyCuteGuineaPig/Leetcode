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