class Solution:
    def countBits(self, num: int) -> List[int]:
        dp = [0 for _ in range(num+1)]
        for i in range(1, num+1):
            dp[i] = dp[i>>1] + (i&1)
        return dp

class Solution:
    def countBits(self, num: int) -> List[int]:
        dp = [0 for _ in range(num+1)]
        offset = 1
        for i in range(1, num+1):
            if i == offset*2:
                offset *= 2
            dp[i] = dp[i-offset] + 1
        return dp

class Solution:
    def countBits(self, num: int) -> List[int]:
        dp = [0 for _ in range(num+1)]
        for i in range(1, num+1):
            dp[i] = dp[i & (i-1)] + 1
        return dp

class Solution:
    def countBits(self, num: int) -> List[int]:
        dp = [0 for _ in range(num+1)]
        for i in range(1, num+1):
            if i & 1:
                dp[i] = dp[i-1] + 1
            else:
                dp[i] = dp[i>>1]
        return dp