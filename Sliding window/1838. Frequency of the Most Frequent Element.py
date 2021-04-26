class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        nums.sort()
        res = 1
        cur = 0
        start = 0
        for i, v in enumerate(nums[1:],1):
            cur += (i - start)*(v-nums[i-1])
            while cur > k and start<=i and start < len(nums):
                cur -= v - nums[start]
                start += 1
            res = max(res, i- start+1)
        return res

"""
valid windows

k  >= windows_size * max - sum

k + sum >= windows_size * max
"""

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        i = 0
        nums.sort()
        for j in range(len(nums)):
            k += nums[j]
            if k < nums[j] * (j - i + 1):
                k -= nums[i]
                i += 1
        return j - i + 1


class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        n = len(nums)
        nums.sort()
        preSum = [0] * (n + 1)
        for i in range(n):
            preSum[i + 1] = preSum[i] + nums[i]

        def getSum(left, right):  # left, right inclusive
            return preSum[right + 1] - preSum[left]

        def count(index): # Count frequency of `nums[index]` if we make other elements equal to `nums[index]`
            left = 0
            right = index
            res = index
            while left <= right:
                mid = left + (right - left) // 2
                s = getSum(mid, index - 1) # get sum of (nums[mid], nums[mid+1]...nums[index-1])
                if s + k >= (index - mid) * nums[index]: # Found an answer -> Try to find a better answer in the left side
                    res = mid  # save best answer so far
                    right = mid - 1
                else:
                    left = mid + 1
            return index - res + 1

        ans = 0
        for i in range(n):
            ans = max(ans, count(i))
        return ans