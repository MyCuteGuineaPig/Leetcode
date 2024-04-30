class Solution:
   def medianOfUniquenessArray(self, A: List[int]) -> int:
        n = len(A)
        total = n * (n + 1) // 2

        def atmost(k):
            res = 0
            count = Counter()
            i = 0
            for j in range(n):
                count[A[j]] += 1
                while len(count) > k:
                    count[A[i]] -= 1
                    if count[A[i]] == 0:
                        del count[A[i]]
                    i += 1
                res += j - i + 1
            return res


        left, right = 1, len(set(A))
        while left < right:
            k = (left + right) // 2
            if atmost(k) * 2 >= total:
                right = k
            else:
                left = k + 1
        return left


class Solution:
    def medianOfUniquenessArray(self, nums: List[int]) -> int:        
        n = len(nums)
        lo, hi = 0, n
        while lo < hi: 
            mid = lo + hi >> 1
            val = ii = 0 
            freq = defaultdict(int)
            for i, x in enumerate(nums): 
                freq[x] += 1
                while len(freq) > mid: 
                    freq[nums[ii]] -= 1
                    if freq[nums[ii]] == 0: freq.pop(nums[ii])
                    ii += 1
                val += i-ii+1
            if val < (n*(n+1)//2+1)//2: lo = mid + 1
            else: hi = mid 
        return lo