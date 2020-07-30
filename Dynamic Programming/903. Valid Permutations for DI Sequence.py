class Solution:
    def numPermsDISequence(self, S: str) -> int:
        dp = [1] * (len(S) + 1)
        for c in S:
            if c == "I":
                dp = dp[:-1] #之前末尾最大是最大的数，不可能再increase
                for i in range(1, len(dp)):
                    dp[i] += dp[i - 1]
            else:
                dp = dp[1:] #之前末尾最大是最小的数，不可能再increase
                for i in range(len(dp) - 1)[::-1]:
                    dp[i] += dp[i + 1]
        return dp[0] % (10**9 + 7)


class Solution:
    def numPermsDISequence(self, S: str) -> int:
        dp = [1] * (len(S) + 1)
        for a, b in zip('I' + S, S):
            dp = list(itertools.accumulate(dp[:-1] if a == b else dp[-1:0:-1]))
            #比如 [1,2,3],  itertools.accumulate ([1,2,3]) = [1,3,6]
        return dp[0] % (10**9 + 7)