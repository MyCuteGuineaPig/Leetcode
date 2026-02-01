class Solution:
    def longestAlternating(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0
        
        cmp = [0]*(n-1)

        for i in range(n-1):
            if nums[i+1] > nums[i]:
                cmp[i] = 1
            elif nums[i+1] < nums[i]:
                cmp[i] = -1 

        left = [1]*n
        for i in range(1, n):
            if cmp[i-1]  != 0 and (i==1 or cmp[i-1] != cmp[i-2]):
                left[i] = left[i-1] + 1 
            else : 
                left[i] = 2 if cmp[i-1] != 0 else 1

        right = [1]*n
        for i in range(n-2, -1, -1):
            if cmp[i] != 0 and (i == n-2 or cmp[i] != cmp[i+1]):
                right[i] = right[i+1] + 1 
            else : 
                right[i] = 2 if cmp[i] != 0 else 1

        res = max(left)
        #print(left, right, cmp)
        for i in range(1, n-1):

            l= left[i-1]
            r = right[i+1]
            if nums[i-1] == nums[i+1]:
                continue

            new_sign = 1 if nums[i+1] > nums[i-1] else -1 
            can = True
            if l >= 2 and i > 1:
                prev_cmp = cmp[i-2]
                if prev_cmp == new_sign:
                    can = False 
            if r >= 2:
                next_cmp = cmp[i+1]
                if next_cmp == new_sign:
                    can = False
            if can:
                res = max(res, l + r)

            
        return res
        