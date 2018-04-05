"""
78. Subsets
"""

from math import pow
from functools import reduce
class Solution:
    def subsets(self, nums):
        return reduce(lambda x, y: [x[i]+[y] if i>>nums.index(y) & 1 else x[i] for i in range(int(pow(2,len(nums))))],nums,[[] for i in range(int(pow(2,len(nums))))])