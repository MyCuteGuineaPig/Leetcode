class Solution:
    def subsequenceSumAfterCapping(self, A: List[int], k: int) -> List[bool]:
        A.sort()
        n = len(A)
        res = [False] * n
        dp = 1
        mask = (1 << k + 1) - 1
        i = 0
        for x in range(1, n + 1):
            while i < n and A[i] <= x:
                dp |= (dp << A[i]) & mask
                i += 1
            v = max(k % x, k - (n - i) * x)
            #print(" dp ", bin(dp))
            #print(x, v, k % x, i,  k - (n - i) * x )
            """
            if k < x: v = k 
            else: 
                如果 k > x: 
                   最多只能有(n - i) * x 个x 作为增加的capped value
                   所以最少需要 k - (n - i) * x 个小于x的元素
                
                或 因为要到sum到 k，所以要从 k%x 的余数开始算

            比如 [4,3,2,4]， k=5,

            当x = 3时候， k% 3 = 2,  k - (n - i) * x = 5 - (4 - 2) * 3 = -1
            """
            for j in range(v, k + 1, x):
                if dp & (1 << j):
                    res[x - 1] = True
                    break
        return res