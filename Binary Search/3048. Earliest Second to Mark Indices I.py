class Solution:
    def earliestSecondToMarkIndices(self, nums: List[int], changeIndices: List[int]) -> int:
        
        n, m = len(nums), len(changeIndices)
        
        def possible(bound):
            cnt = 0 
            last_index = defaultdict(int)
            for i, v in enumerate(changeIndices[:bound]):
                last_index[v] = i 
            if len(last_index) != n:
                return False
            for i in range(bound):
                if last_index[changeIndices[i]] == i:
                    val = nums[changeIndices[i]-1]
                    if cnt < val:
                        return False 
                    else:
                        cnt -= val
                else:
                    cnt += 1 
            return True
            
        l , r = 0, m + 1 
        while l < r: 
            mid = (l+r)//2
            if possible(mid):
                r = mid 
            else:
                l = mid + 1 
        return -1 if l > m else l
                     
        
        
        
        
        
        
        
        
        
                
                
            