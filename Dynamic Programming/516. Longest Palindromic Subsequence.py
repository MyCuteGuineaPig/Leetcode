# Bottom-up
class Solution:
    def longestPalindromeSubseq(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if n == 0: return 0;
        dp = [[0 for _ in range(n)] for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i][i] = 1
            for j in range(i+1, n):
                if s[i] == s[j]: 
                    dp[i][j] = dp[i+1][j-1] +2
                else: 
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        #print(dp)
        return dp[0][n-1]



class Solution:
    def longestPalindromeSubseq(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if s == s[::-1]: return n  #加这个快很多
        if n == 0: return 0;
        dp = [0 for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i] = 1
            prev = 0
            for j in range(i+1, n):
                prev, dp[j] = dp[j], prev+2 if s[i] == s[j] else max(dp[j],dp[j-1])
        #print(dp)
        return dp[-1]

#O(n) space
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        n = len(s)
        dp = [1] * n
        for j in range(1, len(s)):
            pre = dp[j]
            for i in reversed(range(0, j)):
                tmp = dp[i]
                if s[i] == s[j]:
                    dp[i] = 2 + pre if i + 1 <= j - 1 else 2
                else:
                    dp[i] = max(dp[i + 1], dp[i])
                pre = tmp
        return dp[0]

#Top-Down
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        dp = collections.defaultdict(lambda: collections.defaultdict(int))
        
        def topDown(i, j):
            if i > j:
                return 0
            if i == j:
                return 1
            if i in dp and j in dp[i]:
                return dp[i][j]
            
            if s[i] == s[j]:
                dp[i][j] = topDown(i+1, j-1) + 2
            else:
                dp[i][j] = max(topDown(i+1, j), topDown(i,j-1))
            return dp[i][j]
        return topDown(0, len(s)-1)