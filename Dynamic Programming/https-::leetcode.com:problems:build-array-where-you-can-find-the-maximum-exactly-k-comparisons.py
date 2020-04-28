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
            