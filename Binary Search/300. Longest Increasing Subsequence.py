"""
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, 
it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

"""


class Solution:
    def lengthOfLIS(self, nums):
        tail = []
        for num in nums:
            i, j = 0, len(tail)
            while i<j:
                mid = (i+j)>>1
                if num > tail[mid]:
                    i = mid +1
                else: 
                    j = mid
            if i == len(tail):
                tail += [num]
            else:
                tail[i] = num
        return len(tail)
            


class Solution:
    def lengthOfLIS(self, nums):
        tail = []
        for num in nums:
            i = bisect.bisect_left(tail,num)
            if i == len(tail):
                tail += [num]
            else:
                tail[i] = num
        return len(tail)
            



class Solution:
    def lengthOfLIS(self, nums):
        tails = [0] * len(nums)
        size = 0
        for x in nums:
            i, j = 0, size
            while i != j:
                m = int((i + j) / 2)
                #print(" x ",x," i ", i, " j ",j," mid ",m)
                if tails[m] < x:
                    i = m + 1
                else:
                    j = m
            tails[i] = x
            #print("num ",x, " i ", i, tails)
            size = max(i + 1, size)
        return size