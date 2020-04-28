#Top down
class Solution:
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        h = collections.defaultdict(lambda : collections.defaultdict(lambda: collections.defaultdict(int)))
        def dfs(prev, n, k): #prev 之前的最大值
            if k < 0 or n < k or m < k:
                return 0
            if n == 0 and k == 0: #数字用完了，且长度为0，count 1
                return 1
            if k == 0 and n == 1: # prev 是5, k = 0, 长度为1  可以是1;  2;  3;  4;  5
                return prev 
            if n in h and k in h[n] and prev in h[n][k]:
                return h[n][k][prev]
            for i in range(1,m+1):
                if i > prev:
                    h[n][k][prev] += dfs(i, n-1, k-1)  #如果大于之前的最大值，用新的值，k-1
                else:
                    h[n][k][prev] += dfs(prev, n-1, k)
            return h[n][k][prev]
            
        return dfs(0, n, k) % (10**9 + 7)
            

"""
ways[i][j][k] be the number of ways to construct an array of length i with maximum element equal to j at a search cost of k.

1. Clearly, we require ways[i][j][k] += j * ways[i - 1][j][k]. Why? 
    Because if we have an array of length i - 1 with maximum element equal to j at a search cost of k, 
    then we can just append any element from [1, 2, ... j] to this array, 
    and we end up with an array of length i with maximum element equal to j at a search cost of k. 
    Note that neither the search cost nor the maximum element change since we're only appending elements from [1,2, ..., j]. 
    Only the length changes by one.

2. We also require ways[i][j][k] += SUM from x=1 to j-1 of ways[i - 1][x][k - 1] (the sum is inclusive on both ends). 
    This is true because if we have an array of length i - 1 with maximum element (strictly) 
    less than j at a search cost of k - 1, then we can simply append the element j to the end of this array 
    (which adds a comparison cost of one), and we obtain a valid solution.

Now the answer is just the sum over all ways[i][x][k] from x = 1 to k because there is no constraint on what the maximum element should be.
"""

#Bottom up
class Solution:
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        F = collections.defaultdict(lambda : collections.defaultdict(lambda: collections.defaultdict(int)))
        for i in range(1, m+1):
            F[1][i][1] = 1 
        
        for i in range(1,n+1):
            for j in range(1, m+1):
                for k in range(1, k+1):
                    F[i][j][k] += j*F[i-1][j][k]
                    for x in range(1, j):
                        F[i][j][k] += F[i-1][x][k-1]
        
        
        return sum(F[n][i][k] for i in range(1, m+1)) % (10**9 + 7)
            

# Time:  O(n * m * k)
# Space: O(m * k)

class Solution:
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        """
        :type n: int
        :type m: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # dp[l][i][j] = number of ways of constructing array length l with max element i at search cost j
        dp = [[[0]*(k+1) for _ in range(m+1)] for _ in range(2)]
        # prefix_dp[l][i][j] = sum(dp[l][i][j] for i in [1..i])
        prefix_dp = [[[0]*(k+1) for _ in range(m+1)] for _ in range(2)]
        
        for i in range(1, m+1):
            dp[1][i][1] = 1
            prefix_dp[1][i][1] = (prefix_dp[1][i-1][1] + dp[1][i][1])%MOD
        for l in range(2, n+1):
            for i in range(1, m+1):
                for j in range(1, k+1):
                    dp[l%2][i][j] = (i*dp[(l-1)%2][i][j]%MOD + prefix_dp[(l-1)%2][i-1][j-1])%MOD
                    prefix_dp[l%2][i][j] = (prefix_dp[l%2][i-1][j] + dp[l%2][i][j])%MOD  #存了所有dp[l%2][0: i-1][j]
                    #prefix_dp[l%2][i-1][j]： 长度为l%2, 最大数是 i-1, cost 为k, + dp[l%2][i][j]
        return prefix_dp[n%2][m][k]




class Solution:
    #Version 1: DP
    #Top down
    #dp[index, cm, nk] is the number of ways to have nk increasing numbers bigger than cm with length (n-index)
    #O(nkm^2)
    
    def numOfArrays(self, n: int, m: int, k: int) -> int:
        
        def dfs(index, cm, nk, dp):
            if (index, cm, nk) not in dp:
                if index == n:
                    result = int(nk == 0)
                else:
                    result = 0
                    if nk > 0:
                        for s in range(cm+1, m-nk+2):
                            result += dfs(index+1, s, nk-1, dp)
                    result += cm*dfs(index+1, cm, nk, dp)
                dp[index, cm, nk] = result % M
            return dp[index, cm, nk]
            
        M = 10**9 + 7    
        dp = {}
        ans = dfs(0, 0, k, dp)
        #print(dp)
        return ans
    
    
    #Version 2: DP
    #Bottom up
    #dp[i][j][s]: index, cm, nk
    #TC: O(nkm^2), SC:O(nmk)
    
    def numOfArrays(self, n: int, m: int, k: int) -> int:
            
        M = 10**9 + 7    
        dp = [[[0]*(k+1) for j in range(m+1)] for _ in range(n+1)] 
        ans = 0
        for i in range(1, m+1):
            dp[1][i][1] = 1
        
        for a in range(2, n+1):
            for b in range(1, m+1):
                for c in range(1, k+1):
                    count = 0
                    count = (count + b*dp[a-1][b][c]) % M
                    
                    for s in range(1, b):
                        count = (count + dp[a-1][s][c-1]) % M
                    
                    dp[a][b][c] = count
        
        for s in range(k, m+1):
            ans = (ans + dp[n][s][k]) % M
        return ans
    
    
    #Version 3: Improved bottom up
    #Use the technique of prefix sum to get the sum([dp[a-1][s][c-1] for s in range(1, b)])
    #TC: O(nmk), SC: O(nmk)
    
    def numOfArrays(self, n: int, m: int, k: int) -> int:
            
        M = 10**9 + 7    
        dp = [[[0]*(k+1) for j in range(m+1)] for _ in range(n+1)] 
        ans = 0
        for i in range(1, m+1):
            dp[1][i][1] = 1
        for b in range(1, m+1):
            dp[1][b][1] += dp[1][b-1][1]
        
        for a in range(2, n+1):
            for b in range(1, m+1):
                for c in range(1, k+1):
                    count = 0
                    count = (count + b*(dp[a-1][b][c]-dp[a-1][b-1][c])) % M
                    count = (count + dp[a-1][b-1][c-1]) % M
                    dp[a][b][c] = count
            
            for c in range(1, k+1):
                for b in range(1, m+1):
                    dp[a][b][c] = (dp[a][b][c] + dp[a][b-1][c]) % M
        return dp[n][m][k]
    
    
    #Version 4: Improved version 3
    #Since the result of each index only depends on the last index, we can only memorize the result of two layers.
    #TC: O(nmk), SC: O(mk)
    def numOfArrays(self, n: int, m: int, k: int) -> int:
            
        M = 10**9 + 7    
        dp = [[[0]*(k+1) for j in range(m+1)] for _ in range(2)] 
        ans = 0
        for i in range(1, m+1):
            dp[0][i][1] = 1
        for b in range(1, m+1):
            dp[0][b][1] += dp[0][b-1][1]
        
        for a in range(2, n+1):
            for b in range(1, m+1):
                for c in range(1, min(a, b, k)+1):
                    count = 0
                    count = (count + b*(dp[0][b][c]-dp[0][b-1][c])) % M
                    count = (count + dp[0][b-1][c-1]) % M
                    dp[1][b][c] = (count + dp[1][b-1][c]) % M 
            
            #for c in range(1, k+1):
            #    for b in range(1, m+1):
            #        dp[1][b][c] = (dp[1][b][c] + dp[1][b-1][c]) % M
            dp[0], dp[1] = dp[1], dp[0]
        return dp[0][m][k]