"""
44. Wildcard Matching

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
"""

class Solution:
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        m, n = len(s), len(p)
        dp = [[False for _ in range(n+1)] for _ in range(m+1)]
        dp[0][0] = True
        for i in range(n):
            if p[i] == '*': dp[0][i+1] = dp[0][i]
            else: break
        for i in range(m):
            for j in range(n):
                dp[i+1][j+1] = dp[i][j] if p[j] == '?' or s[i] == p[j] else (dp[i][j+1] or dp[i+1][j]) if p[j] == '*' else False
        return dp[-1][-1]

class Solution:
    def isMatch(self, s, p):
        length = len(s)
        if len(p) - p.count('*') > length:
            return False
        dp = [True] + [False]*length
        for i in p:
            if i != '*':
                for n in reversed(range(length)):
                    dp[n+1] = dp[n] and (i == s[n] or i == '?')
            else:
                for n in range(1, length+1):
                    dp[n] = dp[n-1] or dp[n]
            dp[0] = dp[0] and i == '*'
        return dp[-1]

#Greedy
class Solution:
    def isMatch(self, s, p):
        m, n = len(s), len(p)
        i, j, stari, starj = 0, 0, -1, -1 
        while i < m: 
            if j < n and p[j] == '*':
                stari = i
                starj = j 
                j += 1
            elif j < n and (p[j] =='?' or s[i] == p[j]): 
                i += 1 
                j += 1 
            elif stari != -1: 
                stari += 1
                i = stari                
                j = starj + 1
            else: return False
        return j == n or all(i == '*' for i in p[j:])