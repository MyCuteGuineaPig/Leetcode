"""
97. Interleaving String

"""
class Solution:
    def isInterleave(self, s1, s2, s3):
        n1, n2 = len(s1), len(s2)
        if n1 + n2 != len(s3):
            return False
        dp = [[False for _ in range(n2+1)] for _ in range(n1+1)]
        for i in range(n1+1):
            dp[i][0] = (s1[:i] == s3[:i])
        for j in range(n2+1):
            dp[0][j] = (s2[:j] == s3[:j])
        for i in range(1,n1+1):
            for j in range(1,n2+1):
                dp[i][j] = (dp[i-1][j] and s1[i-1] == s3[i+j-1]) or (dp[i][j-1] and s2[j-1] == s3[i+j-1])
        return dp[n1][n2]    
"""
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

    a a b c c
    1 1 0 0 0 
d 0 0 1   
b 0
b 0
c 0
a 0
"""