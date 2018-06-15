"""
632. Smallest Range

Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
"""

import heapq
class Solution:
    def smallestRange(self, nums):
        heap = []
        minv, maxv = float('inf'), float('-inf')
        for i,row in enumerate(nums):
            minv = min(row[0],minv)
            maxv = max(row[0],maxv)
            heapq.heappush(heap, [row[0], 0, i])
        Interval = [minv, maxv]
        while heap:
            [val, i, index]= heapq.heappop(heap)
            if i == len(nums[index])-1:
                 break
            heapq.heappush(heap,[nums[index][i+1],i+1,index])  
            minv = heap[0][0]
            maxv = max(maxv, nums[index][i+1])
                  
            if maxv - minv < Interval[1]-Interval[0]:
                Interval = [minv, maxv]
        return Interval 


#python 2
import heapq
class Solution:
    def smallestRange(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        heap = []
        minv, maxv = float('inf'), float('-inf')
        for row in nums:
            minv = min(row[0],minv)
            maxv = max(row[0],maxv)
            it = iter(row)
            heapq.heappush(heap,(next(it,None),it))
        Interval = [minv, maxv]
        while heap:
            (val, it) = heapq.heappop(heap)
            val = next(it,None)
            if val == None:
                break
            heapq.heappush(heap,(val,it))  
            minv = heap[0][0]
            maxv = max(maxv, val)
                  
            if maxv - minv < Interval[1]-Interval[0]:
                Interval = [minv, maxv]
        return Interval 

"""

For each candidate left bound equal to some value in some array, 
let's determine the next-rightmost value of each array. If it doesn't exist, 
then our left is already too large for any subsequent candidates to have a solution.
Otherwise, we can choose the maximum of these to be the corresponding right bound for our candidate left bound.
We take the maximum of all such candidates.
"""
import heapq
class Solution:
    def smallestRange(self, A):
        pq = [(row[0], i, 0) for i, row in enumerate(A)]
        heapq.heapify(pq)
        
        ans = -1e9, 1e9
        right = max(row[0] for row in A)
        while pq:
            left, i, j = heapq.heappop(pq)
            if right - left < ans[1] - ans[0]:
                ans = left, right
            if j + 1 == len(A[i]):
                return ans
            v = A[i][j+1]
            right = max(right, v)
            heapq.heappush(pq, (v, i, j+1))