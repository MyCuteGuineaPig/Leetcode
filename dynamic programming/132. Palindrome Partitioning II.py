"""
132. Palindrome Partitioning II
"""
class Solution:
    def minCut(self, s):
        """
        :type s: str
        :rtype: int
        """
        if s == s[::-1]: return 0
        if any(s[:i] == s[:i][::-1] and s[i:] == s[i:][::-1] for i in range(1, len(s))): return 1
        dp = [ i-1 for i in range(len(s)+1)]
        n = len(s)
        for i in range(n):
            j = 0
            while i-j>=0 and i+j<n and s[i-j] == s[i+j] :
                dp[i+j+1] = min(dp[i+j+1],dp[i-j]+1)
                j+=1
            j = 0
            while i-j-1>=0 and i+j<n and s[i-j-1] == s[i+j] :
                dp[i+j+1] = min(dp[i+j+1],dp[i-j-1]+1)
                j+=1
        #print(dp)
        return dp[-1]
       