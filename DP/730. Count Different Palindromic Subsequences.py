"""
730. Count Different Palindromic Subsequences
"""
"""
GET TLE
"""
class Solution:
    def countPalindromicSubsequences(self, S):
        """
        :type S: str
        :rtype: int
        """
        n = len(S)
        M = 10**9+7
        dp = [[[0,]*4 for _ in range(n)] for _ in range(3)]
        for length in range(n):
            for i in range(n-1-length,-1,-1):
                for x in range(4):
                    c = chr(97+x) #97 is 'a'
                    if length == 0:
                        dp[2][i][x] = 1 if S[i] == c else 0
                    else:
                        if S[i]!=c:
                            dp[2][i][x] = dp[1][i+1][x]
                        elif S[i+length]!= c:
                            dp[2][i][x] = dp[1][i][x]
                        else: 
                            dp[2][i][x] = 2
                            if length>=2: 
                                for y in range(4):
                                    dp[2][i][x] = (dp[2][i][x]+dp[0][i+1][y])%M
                               
            for j in range(2):
                for i in range(n):
                    for x in range(4):
                        dp[j][i][x] = dp[j+1][i][x]   ## 这里太费时间
        return sum(dp[2][0])%M

"""
ACCEPTED
"""
class Solution:
    def countPalindromicSubsequences(self, S):
        """
        :type S: str
        :rtype: int
        """
        n = len(S)
        M = 10**9+7
        dp = [[[0,]*4 for _ in range(n)] for _ in range(3)]
        for length in range(n):
            for i in range(n-1-length,-1,-1):
                cur, prev1, prev2 = length%3, (length-1)%3, (length-2)%3
                for x in range(4):
                    c = chr(97+x) #97 is 'a'
                    if length == 0:
                        dp[cur][i][x] = 1 if S[i] == c else 0
                    else:
                        if S[i]!=c:
                            dp[cur][i][x] = dp[prev1][i+1][x]
                        elif S[i+length]!= c:
                            dp[cur][i][x] = dp[prev1][i][x]
                        else: 
                            dp[cur][i][x] = 2
                            if length>=2: 
                                for y in range(4):
                                    dp[cur][i][x] = (dp[cur][i][x]+dp[prev2][i+1][y])%M
                               
        return sum(dp[(n-1)%3][0])%M

class Solution:
    def countPalindromicSubsequences(self, S):
        """
        :type S: str
        :rtype: int
        """
        n = len(S)
        M = 10**9+7
        dp = [[0,]*n for _ in range(n)]
        for i in range(n-1,-1,-1):
            dp[i][i] = 1
            for j in range(i+1,n):
                if S[i]==S[j]:
                    left = i+1
                    right = j-1
                    while left<=right and S[left] != S[j]:
                        left+=1
                    while left<=right and S[right] != S[i]:
                        right-=1
                    if left>right :
                        dp[i][j] = dp[i+1][j-1]*2 + 2
                        #所有的中间都乘以2，比如aba, b=1, aba = 2*1+2, 因为加上头和尾又可以组成新的回体字，2是因为头尾两个字可以单组，又可以一个单拿出来(aa,a)
                    elif left == right:
                        dp[i][j] = dp[i+1][j-1]*2 + 1
                        #所有的中间都乘以2，比如aaa, b=1, aba = 2*1+1, 因为加上头和尾又可以组成新的回体字，1是因为头尾两个字可以单组，但不能单拿出来
                    else:
                        dp[i][j] = dp[i+1][j-1]*2 - dp[left+1][right-1]
                        #比如"aabcaa"  //abca = 6， 把它乘以2，但是要减去里面的
                        #aabcaa, abca*2 = 12 - 2(bc) = 10, 减去原因因为外面的a(0)ca(5),a(0)ba(0), 和中间的a(1)ca(4),a(1)ba(4) 一样的。

                else:
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
                dp[i][j] = dp[i][j]%M
        return dp[0][n-1]
