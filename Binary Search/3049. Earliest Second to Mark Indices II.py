"""

需要first index: 因为想要尽早的set nums = 0 


a. Why backwards? 
Because after zeroing out a number you have to make sure that there is enough time to mark it as well. 
By going backwards we can keep track of the available time in the future.

当time_available==0 时候, 必须要drop 一个, time_available == 0 表示后面没有时间来heap中的点

最后heap 保留的是，最大number可以被zero out的

"""
class Solution:
    def earliestSecondToMarkIndices(self, nums: List[int], changeIndices: List[int]) -> int:
        first_index = defaultdict(int)
        for i, v in enumerate(changeIndices):
            if v not in first_index and nums[v-1]!=0:
                #如果v 是0, mark的机会被这里算  len(nums) - len(q)
                first_index[v] = i 

        first_index_to_value = {i:v for v, i in first_index.items()}
        n, m = len(nums), len(changeIndices)
        print("first_index_to_value ",first_index_to_value)
        def possible(bound):
            q = []
            time_available = 0
            for i in range(min(bound,m)-1, -1, -1):
                if i in first_index_to_value:
                    heapq.heappush(q, nums[first_index_to_value[i]-1])
                    if time_available:
                        time_available -= 1 
                    else:
                        time_available += 1 
                        heapq.heappop(q) #因为把之前的push value清理走了, 加一个时间
            
                else:
                    time_available += 1 
            
            # sum(nums) - sums(q) different between target and can be set as 0 
            # len(nums) - lens(q): time required to mark value 
            decrement_total = sum(nums) - sum(q) + len(nums) - len(q)
            mark_as_zero = len(q) * 2 # set 一次，mark 一次
            #print("q ", q, "decrement_total", decrement_total, "mark_as_zero", mark_as_zero)
            return decrement_total + mark_as_zero <= bound

        low, high = 0, m+1
        while low < high:
            mid = (low + high)//2
            if possible(mid):
                high = mid
            else:
                low = mid + 1 
        return low if low <= m else -1
         decrement_total 3 nums_total 4 q_total 2 heap.size() 1 mark_zero 2
