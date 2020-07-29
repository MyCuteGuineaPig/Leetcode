# Top-Down
class Solution:
    def largestSumOfAverages(self, A: List[int], K: int) -> float:
        memo = {}
        def search(n, k):
            if (n, k) in memo: return memo[n, k]
            if n < k: return 0
            if k == 1:
                memo[n, k] = sum(A[:n]) / float(n)
                return memo[n, k]
            cur, memo[n, k] = 0, 0
            for i in range(n - 1, 0, -1):
                cur += A[i]
                memo[n, k] = max(memo[n, k], search(i, k - 1) + cur / float(n - i))
            return memo[n, k]
        return search(len(A), K)

# Bottom-up
class Solution:
    def largestSumOfAverages(self, A: List[int], K: int) -> float:
        n = len(A)
        dp=[[0 for _ in range(n)] for _ in range(K)]
        
        for i in range(n):
            dp[0][i] = sum(A[:i+1])/(i+1)
        
        for k in range(1,K): 
            for i in range(k,len(A)):
                if k ==0:
                    dp[k][i]=sum(A[:i+1])/(i+1)
                else:
                    for j in range(k,i+1):
                        dp[k][i]=max(dp[k-1][j-1]+sum(A[j:i+1])/(i-j+1),dp[k][i])


        return dp[-1][-1]