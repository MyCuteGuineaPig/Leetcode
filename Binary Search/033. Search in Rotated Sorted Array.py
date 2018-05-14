"""
33. Search in Rotated Sorted Array

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1


"""
class Solution:
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        l, r = 0, len(nums)-1
        while l<=r:
            mid = (l+r)>>1
            if nums[mid] == target: return mid
            #print(l,r,mid,nums[mid])
            if target>nums[mid]:
                if nums[mid]<nums[l] and nums[l]<=target: r = mid-1
                else: l = mid+1
            else:
                if nums[mid]>=nums[l] and nums[l]>target: l = mid+1
                else: r = mid-1
            #print(l,r,mid)
        return -1


"""
Explanation
My solutions use binary search guided by the following thoughts:

Remember the array is sorted, except it might drop at one point.

If nums[0] <= nums[i], then nums[0..i] is sorted (in case of "==" it's just one element, and in case of "<" there must be a drop elsewhere). 
So we should keep searching in nums[0..i] if the target lies in this sorted range, i.e., if nums[0] <= target <= nums[i].

If nums[i] < nums[0], then nums[0..i] contains a drop, and thus nums[i+1..end] is sorted and lies strictly between nums[i] and nums[0]. 
So we should keep searching in nums[0..i] if the target doesn't lie strictly between them, i.e., if target <= nums[i] < nums[0] or nums[i] < nums[0] <= target

Those three cases look cyclic:

    nums[0] <= target <= nums[i]
               target <= nums[i] < nums[0]
                         nums[i] < nums[0] <= target
So I have the three checks (nums[0] <= target), (target <= nums[i]) and (nums[i] < nums[0]), and I want to know whether exactly two of them are true.
 They can't all be true or all be false (check it), so I just need to distinguish between "two true" and "one true".
  Parity is enough for that, so instead of adding them I xor them, which is a bit shorter and particularly helpful in Java and Ruby, 
  because those don't let me add booleans but do let me xor them.

(Actually while developing this I thought of permutations of nums[0], target and nums[i] and the permutation parity and
 saw those three checks as representing inversions,
  but I had trouble putting that into words and now find the above explanation much better. But it helped me get there, so I wanted to mention it here.)
"""

class Solution:
    def search(self, nums, target):
        lo, hi = 0, len(nums) - 1
        while lo < hi:
            mid = (lo + hi)>>1
            if (nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]): #只能有一个正确
                lo = mid + 1
            """
            like [4,5,6,7,0,1,2] target = 1, mid = 7
            no turn from nums[0] to nums[mid]: so this is a turn between nums[mid] to nums[r]
                target<nums[mid] && nums[0] < nums[mid] and want to move right:  nums[0]> target 

            like [4,5,6,7,0,1,2] target = 1, mid = 0
            a turn from nums[0] to nums[mid]: nums[0] > nums[mid]
                then nums[mid]<target, and want to move right:  nums[0]> target 
            
            If there is no turn from [1,2,3,4,5,6,7], mid = 5, target = 6
            if there is a no turn from nums[0] to nums[mid] and nums[mid] to nums[r]  
                target > nums[mid] && nums[0] <= nums[mid] and nums[0]<target

            """
            else:
                hi = mid
        return lo if target in nums[lo:lo+1] else -1


class Solution:
    def search(self, nums, target):
        self.__getitem__ = lambda i: \
            (nums[0] <= target) ^ (nums[0] > nums[i]) ^ (target > nums[i])
        i = bisect.bisect_left(self, True, 0, len(nums))
        return i if target in nums[i:i+1] else -1