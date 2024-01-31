class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        count = [0] * 30
        for a in nums:
            for i in range(30):
                if a & (1 << i):
                    count[i] += 1
        res = 0
        mod = 10 ** 9 + 7
        for j in range(k):
            cur = 0
            for i in range(30):
                if count[i]:
                    count[i] -= 1
                    cur |= 1 << i
            res = (res + cur * cur % mod) % mod
        return res

class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        count = Counter(i for a in nums for i in range(32) if a & (1 << i))
        return sum(sum((count[i] > j) << i for i in range(32)) ** 2 for j in range(k)) % (10 ** 9 + 7)



class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        IDX = [0] * 32
        ans = [0] * n
        
        for x in nums:
            for i in range(32):
                if (x >> i) & 1:
                    ans[IDX[i]] += 1 << i
                    IDX[i] += 1
    
        res = 0 
        mod = 10**9 + 7
        
        for i in range(k):
            res += ans[i] ** 2
            res %= mod 
            
        return res