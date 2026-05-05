class Solution:
    def maxFixedPoints(self, nums: list[int]) -> int:
        candidates = []
        for i, val in enumerate(nums):
            if val <= i:  #只有当val <= i时，才有可能存在固定点，且固定点的值一定小于等于i
                d = i-val 
                candidates.append((d, val))
        print(candidates)
        candidates.sort()
        t = []
        for d, val in candidates: 
            idx = bisect.bisect_left(t, val)
            if idx < len(t):
                t[idx] = val 
            else:
                t.append(val)
        return len(t)
        
