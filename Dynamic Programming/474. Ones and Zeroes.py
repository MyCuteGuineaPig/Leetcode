
#Bottom-up

class Solution:
    def findMaxForm(self, strs, m, n):
        """
        :type strs: List[str]
        :type m: int
        :type n: int
        :rtype: int
        """
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]
        for s in strs:
            c0 = s.count('0')
            c1 = s.count('1')
            for i in range(m, c0-1,-1):
                for j in range(n,c1-1,-1):
                    dp[i][j] = max(dp[i-c0][j-c1]+1, dp[i][j])
        return dp[-1][-1]

# Top-Down
class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = collections.defaultdict(lambda: collections.defaultdict(lambda: collections.defaultdict(int)))
        
        def topDown(m, n, pos):
            if pos == len(strs) or m < 0 or n < 0 or m == 0 and n == 0: 
                return 0
            if pos in dp and m in dp[pos] and n in dp[pos][m]:
                return dp[pos][m][n]
            
            i0 = strs[pos].count('0')
            i1 = strs[pos].count('1')
            
            if i0 <= m and i1 <= n: 
                dp[pos][m][n] = topDown(m - i0, n-i1, pos+1)+1
                
            dp[pos][m][n] = max(dp[pos][m][n], topDown(m, n, pos+1))
            return dp[pos][m][n]
        return topDown(m, n, 0)

#Top-Down 必须sort，不sort error
class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = collections.defaultdict(lambda: collections.defaultdict(int))
        strs.sort(key = len) # 必须要sort
        def topDown(m, n, pos):
            #print(m, n, pos)
            if pos == len(strs) or m < 0 or n < 0 or m == 0 and n == 0: 
                return 0
            if  m in dp and n in dp[m]:
                return dp[m][n]
            
            cur = 0 
            for i, s in enumerate(strs[pos:],pos):
                i0 = s.count('0')
                i1 = s.count('1')
                if i0 <= m and i1 <= n: 
                    cur = max(cur, topDown(m - i0, n-i1, i+1)+1)
            dp[m][n] = cur
            return dp[m][n]
        return topDown(m, n, 0)