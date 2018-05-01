"""
689. Maximum Sum of 3 Non-Overlapping Subarrays
"""

class Solution:
    def maxSumOfThreeSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        P, cur = [], 0
        for i in range(n):
            cur += nums[i]
            if i>=k-1:
                P.append(cur)
                cur -= nums[i-k+1]
        left, right = [0]*(n-k+1), [n-k,]*(n-k+1)
        for i in range(1,len(P)):
            if P[i]>P[left[i-1]]: # left[i+1] best sum index before i
                left[i] = i
            else:
                left[i] = left[i-1]
        for i in range(n-k-1,-1,-1):
            if P[i]>=P[right[i+1]]: # right[i+1] best sum index after i
                right[i] = i
            else:
                right[i] = right[i+1]

        res, lis = P[0]+P[k]+P[2*k], [0, k, 2*k]
        for i in range(k,n-2*k+1):
            print(i, i-k, i+k)
            if res<P[left[i-k]] + P[i]+P[right[i+k]]:
                res = P[left[i-k]] + P[i]+P[right[i+k]]
                lis = [left[i-k], i,  right[i+k]]
            
        return lis
        
                






class Solution:
    def maxSumOfThreeSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        P, cur = [0,]*(n-k+1), 0
        P[0] = sum(nums[:k])
        for i in range(1,n-k+1):
            P[i] = P[i-1] + nums[i+k-1] - nums[i-1]

        left, right = [0]*(n-k+1), [n-k,]*(n-k+1)
        for i in range(1,len(P)):
            if P[i]>P[left[i-1]]: # left[i+1] best sum index before i
                left[i] = i
            else:
                left[i] = left[i-1]
        for i in range(n-k-1,-1,-1):
            if P[i]>=P[right[i+1]]: # right[i+1] best sum index after i
                right[i] = i
            else:
                right[i] = right[i+1]

        res, lis = 0, []
        for i in range(k,n-2*k+1):
            if res<P[left[i-k]] + P[i]+P[right[i+k]]:
                res = P[left[i-k]] + P[i]+P[right[i+k]]
                lis = [left[i-k], i,  right[i+k]]
            
        return lis