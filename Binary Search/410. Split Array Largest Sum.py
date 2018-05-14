"""
410. Split Array Largest Sum

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

"""
class Solution(object):
    def splitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        def IsEnough(m,t):
            cnt = 0
            for n in nums:
                cnt += n
                if cnt > t:
                    m-=1
                    if m==0:
                        return False
                    cnt = n
            return True

        maxnum, totsum = max(nums),sum(nums)
        if m==0: return totsum
        if m==len(nums): return maxnum
        l, r= maxnum, totsum
        while l < r:
            mid = (l + r)>>1
            if IsEnough(m,mid): r = mid
            else:  l = mid + 1
        return l

