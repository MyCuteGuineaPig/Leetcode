class Solution:
    def goodBinaryStrings(self, minLength: int, maxLength: int, oneGroup: int, zeroGroup: int) -> int:
        # MOD is the modulo constant for the result
        MOD = 10**9 + 7
        
        # Initializing a dynamic programming (dp) list to track the count of good binary strings 
        # of length i. Start with dp[0] = 1 since there's one way to create a binary string of length 0.
        dp = [0] * (maxLength + 1)
        dp[0] = 1

        # Iterate over possible string lengths from 1 to maxLength.
        for i in range(1, maxLength + 1):
            # If it's possible to append a group of ones of size oneGroup
            # to a previously shorter good string, then add that count to dp[i].
            if oneGroup <= i:
                dp[i] += dp[i - oneGroup]
            
            # Similarly, if it's possible to append a group of zeros of size zeroGroup
            # to a previously shorter good string, then add that count to dp[i].
            if zeroGroup <= i:
                dp[i] += dp[i - zeroGroup]

        # Return the sum of good binary strings of length between minLength and maxLength, inclusive.
        # Then, take the result modulo MOD to keep the number from getting too large.
        return sum(dp[minLength:maxLength+1]) % MOD


class Solution:
    def goodBinaryStrings(self, minLength: int, maxLength: int, oneGroup: int, zeroGroup: int) -> int:
        dp = [0] * (maxLength+1)
        for i in range(maxLength, -1, -1): 
            if i>=minLength: dp[i] += 1
            if i+oneGroup <= maxLength: dp[i] += dp[i+oneGroup]
            if i+zeroGroup <= maxLength: dp[i] += dp[i+zeroGroup]
            dp[i] %= 1_000_000_007 
        return dp[0]