class Solution:
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:
        if sum(nums) % k != 0:
            return False 
        self.target = sum(nums) // k
        if any(i> self.target for i in nums):
            return False
        def dfs (start, cur, k):
            if cur ==  self.target and k == 1: 
                #print("return True")
                return True
            elif cur == self.target:
                cur = 0 
                k -= 1
                start = 0 #start back to 0 这个重要, Or 最后之前有的跳过了, start = len(nums), k!=1, return False 就reset nums了, 
            for i, v in enumerate(nums[start:],start):
                if v >0 and cur + v <= self.target:
                    nums[i] *= -1 
                    if dfs(i + 1, cur + v, k): 
                        return True 
                    nums[i] *= -1 
            return False 
        return dfs(0, 0, k)
        
        
class Solution:        
    def canPartitionKSubsets(self, A, k):
        if len(A) < k:
            return False
        ASum = sum(A)
        A.sort(reverse=True)
        if ASum % k != 0:
            return False
        target = [ASum / k] * k

        def dfs(pos):
            if pos == len(A): return True
            for i in xrange(k):
                if target[i] >= A[pos]:
                    target[i] -= A[pos]
                    if dfs(pos + 1):
                        return True
                    target[i] += A[pos]
            return False
        return dfs(0)
