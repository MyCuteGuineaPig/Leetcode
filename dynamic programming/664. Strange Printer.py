"""
664. Strange Printer

"abab"
return 3,  aaaa, then bbb, then a 

"ababab"
return 4

aaaaaa
 bbbbb
  aaa
   b


        a  b  c  a  b  c
    a   1  2  3  3  4  5
    b      1  2  3  3  4 
    c         1  2  3  3 
    a            1  2  3 
    b               1  2
    c                  1

        a  a  a  b  b  b
    a   1  1  1  2     
    a      1  1  2      
    a         1  2     1 
    b            1  1  1 
    b               1  1
    b                  1


"""

class Solution:
    def strangePrinter(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        if n == 0: return 0
        dp = [[0,]*(n) for _ in range(n)]
        for i in range(n-1,-1, -1):
            dp[i][i] = 1
            for j in range(i+1,n):
                dp[i][j] = dp[i+1][j]+1
                for k in range(i+1,j+1):
                    if s[i] == s[k]:
                        dp[i][j] = min(dp[i][j], dp[i+1][k-1]+dp[k][j])
        return dp[0][n-1]

