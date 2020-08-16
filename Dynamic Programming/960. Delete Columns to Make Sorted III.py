class Solution:
    def minDeletionSize(self, A: List[str]) -> int:
        n = len(A[0])
        dp = [1] * n
        for j in range(1, n):
            for i in range(j):
                if all(a[i] <= a[j] for a in A):
                    dp[j] = max(dp[j], dp[i] + 1)
        return n - max(dp)


class Solution:
    def minDeletionSize(self, A: List[str]) -> int:
        cache = {}
        def solve(A, index, start):
            if index >= len(A): return 0
            if (index, start) in cache: return cache[index,start]
            
            if any(A[index][j] < start[j] for j in range(len(A[index]))):
                cache[index,start] = 1 + solve(A, index+1, start)
                return cache[index,start]
            
            cache[index,start] = min(solve(A,index+1,tuple(A[index])), 1+solve(A,index+1, start))
            return cache[index,start]
        
        return solve(list(zip(*A)), 0, tuple(['a']*len(A)))