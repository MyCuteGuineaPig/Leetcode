"""
239. Sliding Window Maximum

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
"""

class Solution:
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        dq = collections.deque()
        res = []
        for i, v in enumerate(nums):
            count = 0
            while dq and dq[-1][0] < v:
                count += dq[-1][1]+1
                dq.pop()
            dq.append([v,count])
            if i>=k-1:
                res.append(dq[0][0])
                if dq[0][1] == 0:
                    dq.popleft()
                else: dq[0][1] -=1
        return res


class Solution:
    def maxSlidingWindow(self, nums, k):
        dq = collections.deque()
        res = []
        for i, v in enumerate(nums):
            while dq and nums[dq[-1]]<=v:
                dq.pop()
            dq.append(i)
            if i>=k-1:
                res.append(nums[dq[0]])
                if dq[0] == i-k+1:
                    dq.popleft()
        return res