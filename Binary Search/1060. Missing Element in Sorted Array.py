"""
r = len(nums)

if f(mid) < k:
    l = mid + 1  可能会从miss number的left interval 跳过
else:
    r = mid 

比如 nums = [4,7,9,10] k = 3, ans = 8
Missing number 的left interval index 为1 (7)

l = 0, r = 4, mid = 2, f(mid) = 3 =>  r = 2
l = 0, r = 2, mid = 1, f(mid) = 2 =>  l = 2,  跳过index 1

比如 nums = [1，2，4] k = 3, ans = 6
Missing number 的left interval index 为2 (4)

l = 0, r = 3, mid = 1, f(mid) = 0 =>   l = 2
l = 2, r = 3, mid = 2, f(mid) = 1 =>  l = 3,  跳过index 2 

"""
class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        f =  lambda i: nums[i] - nums[0] - i
        l, r = 0, len(nums) 
        while l < r:
            mid = (l + r)//2
            if f(mid) < k:
                l = mid + 1
            else:
                r = mid 
        return nums[l-1] + k - f(l-1) 




class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        f =  lambda i: nums[i] - nums[0] - i
        l, r = 0, len(nums)-1
        if k > f(r):
            return nums[r] + k - f(r)
        
        while l < r:
            mid = (l + r)//2
            if f(mid) < k:
                l = mid + 1
            else:
                r = mid 
        return nums[l-1] + k - f(l-1) 


class Solution(object):
    def missingElement(self, nums, k):
        l,r=0,len(nums)-1
        
        while l<r:
            mid=(l+r+1)//2
            if nums[mid]-nums[0]-mid < k: #count the number of missing from the begining to mid point
                l=mid
            else:
                r=mid-1
            
        return nums[0]+k+l



class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        f =  lambda i: nums[i] - nums[0] - i
        if not nums or k == 0:
            return 0
        
        l, r = 0, len(nums) - 1
        if k > f(r): # if k is larger than the number of mssing words in sequence
            return nums[-1] + k - f(r)
        
        
        while l + 1 < r:
            mid = (l + r) // 2
            print(l, r, mid, f(mid))
            if f(mid) < k:
                l = mid
            else:
                r = mid
        return nums[l] + k - f(l) # k should be between left and right index in the end


class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        f =  lambda i: nums[i] - nums[0] - i
        if not nums or k == 0:
            return 0
        
        left, right = 0, len(nums) - 1
        if k > f(right): # if k is larger than the number of mssing words in sequence
            return nums[-1] + k - f(right)
        
       
        while left + 1 < right:
            mid = (left + right) // 2
            missing = nums[mid] - nums[left] - (mid - left)
            if missing < k:
                left = mid
                k -= missing # KEY: move left forward, we need to minus the missing words of this range
            else:
                right = mid
                
        return nums[left] + k # k should be between left and right index in the end