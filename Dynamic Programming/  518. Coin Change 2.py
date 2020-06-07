#Bottom-up
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        dp = [0] * (amount + 1)
        dp[0] = 1
        for i in coins:
            for j in range(1, amount + 1):
               if j >= i:
                   dp[j] += dp[j - i]
        return dp[amount]

#Top-Down
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        dp = collections.defaultdict(lambda: collections.defaultdict(int))
        def topDown(cur, pos):
            if cur == 0:
                return 1
            if cur < 0 or pos == len(coins):
                return 0
            if pos in dp and cur in dp[pos]:
                return dp[pos][cur]
            
            dp[pos][cur] = topDown(cur - coins[pos], pos) + topDown(cur, pos+1)
            return dp[pos][cur]
        return topDown(amount, 0)