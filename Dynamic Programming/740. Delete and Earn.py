# 2020 bottom-up
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        cnt = [0 for _ in range(10001)]
        for i in nums:
            cnt[i] += i
        take, skip = cnt[1], 0
        for i in cnt:
            take, skip = max(skip + i, take), take
        return take

# 2020 bottom-up
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        cnt = [0 for _ in range(10001)]
        for i in nums:
            cnt[i] += i
        dp = [0 for _ in range(10001)]
        dp[1] = cnt[1]
        for i in range(2, 10001):
            dp[i] = max(dp[i-1], dp[i-2] + cnt[i])
        return dp[-1]

# 2020 Top-Down
class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        cnt = [0 for _ in range(10001)]
        for i in nums:
            cnt[i] += i
        dp = [0 for _ in range(10001)]
        dp[1] = cnt[1]
        def topDown(i):
            if i<= 1 or dp[i] > 0:
                return dp[i]
            dp[i] = max(topDown(i-1), topDown(i-2) + cnt[i])
            return dp[i]
        return topDown(10000)