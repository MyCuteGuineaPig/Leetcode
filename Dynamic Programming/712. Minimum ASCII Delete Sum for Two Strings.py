"""
712. Minimum ASCII Delete Sum for Two Strings
"""
class Solution:
    def minimumDeleteSum(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        n1, n2 = len(s1), len(s2)
        dp = [0]*(n2+1)
        for i in range(n2):
            dp[i+1]= dp[i]+ord(s2[i])

        for i in range(n1):
            prev = dp[0]
            dp[0] += ord(s1[i])
            for j in range(n2): 
                prev, dp[j+1] = dp[j+1], prev if s1[i] == s2[j] else min(ord(s1[i])+dp[j+1], ord(s2[j])+dp[j])
        return dp[-1]


class Solution:
    def minimumDeleteSum(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        l1, l2 = len(s1), len(s2)
        dp = [[0] * (l2 + 1) for _ in range(l1 + 1)]
        for i in range(l1):
            for j in range(l2):
                if s1[i] == s2[j]:
                    dp[i + 1][j + 1] = dp[i][j] + ord(s1[i])  
                else:
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j])
        result = sum(map(ord, s1 + s2)) - dp[l1][l2] * 2 #不一样减去一样的
        return result
            