"""
78. Subsets
"""

from math import pow
from functools import reduce
class Solution:
    def subsets(self, nums):
        return reduce(lambda x, y: [x[i]+[y] if i>>nums.index(y) & 1 else x[i] for i in range(int(pow(2,len(nums))))],nums,[[] for i in range(int(pow(2,len(nums))))])

 



#2020
import functools
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        return functools.reduce(lambda x, digit: [x[i] + [digit] \
                    if 1 << nums.index(digit) & i else x[i] \
                            for i in range(2**n) ], nums, [[] for _ in range(2**n)])

#2020
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        cur, res = [], []
        def dfs(start):  
            if start <= len(nums):
                res.append([i for i in cur])
                for i, v in enumerate(nums[start:],start):
                    cur.append(v)
                    dfs(i+1)
                    cur.pop()
        dfs(0)
        return res

#2020
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = [[]]
        for i in nums:
            size = len(res)
            for j in range(size):
                res.append([v for v in res[j]])
                res[-1] += [i]
        return res

#2020
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        res = [[] for _ in range(2**n)]
        for i, v in enumerate(nums):
            for j in range(2**n):
                if 1 << i & j:
                   res[j].append(v) 
        return res
    
#2021
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        return functools.reduce(lambda x, y: x + [l + [y] for l in x], nums, [[]])
            
