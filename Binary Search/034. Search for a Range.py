"""
34. Search for a Range
"""
class Solution:
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        l, r = 0, len(nums)-1
        while l<r and nums[l]!=target:
            mid = (l+r)>>1
            if nums[mid]<target:
                l = mid+1
            else:
                r = mid
        if l<len(nums) and nums[l] == target:
            tl = l
            while l<len(nums)-1 and nums[l+1] == target: l+=1
            return [tl, l]
        return [-1,-1]

class Solution:
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        l, r = 0, len(nums)-1
        while l<r and (nums[l]!=target or nums[r]!=target):
            mid = (l+r)>>1
            if nums[mid]<target:
                l = mid+1
            else:
                if nums[l]!=target : l+=1
                elif nums[r]!=target: r-=1
        if l<len(nums) and r>=0 and nums[l] == target and nums[r] == target:
            return [l, r]
        return [-1,-1]




"""
先search target 如果target 在num中,找比target 大1的数，这个数减一是答案
"""

def searchRange(self, nums, target):
    def search(n):
        lo, hi = 0, len(nums)
        while lo < hi:
            mid = (lo + hi) / 2
            if nums[mid] >= n:
                hi = mid
            else:
                lo = mid + 1
        return lo
    lo = search(target)
    return [lo, search(target+1)-1] if target in nums[lo:lo+1] else [-1, -1]

"""
divide conquer

The search helper function returns an index range just like the requested searchRange function, 
but only searches in nums[lo..hi]. It first compares the end points and immediately returns [lo, hi] if that whole part of nums is full of target, 
and immediately returns [-1, -1] if target is outside the range. The interesting case is when target can be in the range but doesn't fill it completely.

In that case, we split the range in left and right half, 
solve them recursively, 
and combine their results appropriately. Why doesn't this explode exponentially? Well, 
let's call the numbers in the left half A, ..., B and the numbers in the right half C, ..., D. 
Now if one of them immediately return their [lo, hi] or [-1, -1], then this doesn't explode. 
And if neither immediately returns, 
that means we have A <= target <= B and C <= target <= D. 
And since nums is sorted, we actually have target <= B <= C <= target, 
so B = C = target. The left half thus ends with target and the right half starts with it. 
I highlight that because it's important. Now consider what happens further. 
The left half gets halved again. Call the middle elements a and b, so the left half is A, ..., a, b, ..., B. Then a <= target and:

If a < target, then the call analyzing A, ..., a immediately returns [-1, -1] and we only look further into b, ..., B which is again a part that ends with target.
If a == target, then a = b = ... = B = target and thus the call analyzing b, ..., B immediately returns its [lo, hi] and we only look further into A, ..., 
a which is again a part that ends with target.
Same for the right half C, ..., D. So in the beginning of the search, 
as long as target is only in at most one of the two halves (so the other immediately stops), 
we have a single path. And if we ever come across the case where target is in both halves, 
then we split into two paths, but then each of those remains a single path. And both paths are only O(log n) long, so we have overall runtime O(log n).

"""
def searchRange(self, nums, target):
    def search(lo, hi):
        if nums[lo] == target == nums[hi]:
            return [lo, hi]
        if nums[lo] <= target <= nums[hi]:
            mid = (lo + hi) / 2
            l, r = search(lo, mid), search(mid+1, hi)
            return max(l, r) if -1 in l+r else [l[0], r[1]]
        return [-1, -1]
    return search(0, len(nums)-1)


"""
use bisect.bisect_left, bisect,bisect_right
"""
class Solution:
    def searchRange(self, nums, target):
        lo = bisect.bisect_left(nums,target)
        return [lo, bisect.bisect_right(nums,target)-1] if target in nums[lo:lo+1] else [-1,-1]

