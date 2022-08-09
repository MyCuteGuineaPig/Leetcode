class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        def getSum(num):
            x = 0
            while num: 
                x += num % 10
                num = num // 10
            return x
        
        st = collections.defaultdict(list)
        for i in nums:
            cursum = getSum(i)
            heapq.heappush(st[cursum], i)
            if len(st[cursum]) > 2:
                heapq.heappop(st[cursum])
        maxsum = -1 
        for k, v in st.items():
            if len(v) == 2:
                maxsum = max(maxsum, sum(v))
        return maxsum
                
                