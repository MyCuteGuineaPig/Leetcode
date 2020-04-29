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


class Solution:
    def minCut(self, s: str) -> int:
        F = collections.defaultdict(int)
        ispal = collections.defaultdict(lambda: collections.defaultdict(int))
        n = len(s)
        for i in range(0, n+1):
            F[i] = i-1
            ispal[i][i] = 1
            
        for k in range(1,n):
            for i in range(k+1): #比如更新 aab, b pal is 1
                if s[k] == s[i] and ( k-i < 2 or ispal[i+1][k-1]):
                    ispal[i][k] = 1
                    F[k+1] = min(F[k+1], F[i]+1)
        #print(F)
        return F[n]

"""
Time Out 
Complexity O(n^3)
"""

class Solution:
    def minCut(self, s: str) -> int:
        F = collections.defaultdict(lambda: collections.defaultdict(int))
        n = len(s)
        for i in range(n):
            F[i][i] = 0
            
        for k in range(1,n):
            for i in range(0, n-k):
                if s[i] == s[i+k] and F[i+1][i+k-1] == 0:
                    F[i][i+k] = 0
                else:
                    res = k+1
                    for j in range(i, i+k):
                        res = min(res, F[i][j] + F[j+1][i+k] + 1)
                    F[i][i+k] = res
                #print(i, i+k, F[i][i+k])
        
        
        return F[0][n-1]
       