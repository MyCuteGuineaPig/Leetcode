class Solution:
    def kBigIndices(self, nums: List[int], k: int) -> int:
        prefix = [False] * len(nums)
        pq = []
        for i, x in enumerate(nums): 
            if len(pq) == k and -pq[0] < x: prefix[i] = True
            heappush(pq, -x)
            if len(pq) > k: heappop(pq)
        ans = 0 
        pq = []
        for i, x in reversed(list(enumerate(nums))): 
            if len(pq) == k and -pq[0] < x and prefix[i]: ans += 1
            heappush(pq, -x)
            if len(pq) > k: heappop(pq)
        return ans 


class Solution:
    def kBigIndices(self, A: List[int], k: int) -> int:
        def count(A,is_reversed = True):
            N = len(A)
            BIT = Counter()
            M = max(A) + 1
            def count(x):
                s = 0
                while x:
                    s += BIT[x]
                    x -= x & (-x)
                return s
            
            def update(x):
                while x < M+1:
                    BIT[x] += 1
                    x += x & (-x)

            ans = set()
            for i,a in enumerate(A):
                c = count(a-1)
                
                if c >= k:
                    if is_reversed:
                        ans.add(i)
                    else:
                        ans.add(N-1-i)
                update(a)
            return ans
        
        
        a1 = count(A)
        a2 = count(A[::-1], False)
        return len(a1&a2) 