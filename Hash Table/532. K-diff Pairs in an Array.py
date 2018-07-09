"""
532. K-diff Pairs in an Array


Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
"""

class Solution:
    def findPairs(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        if k < 0: return 0
        dic = collections.Counter(nums)
        res = 0
        for i, v in dic.items():
            if k == 0: res += v > 1
            elif i + k in dic:
                res += 1
        return res
"""
which is equivalent to:

def findPairs(self, nums, k):
        c = collections.Counter(nums)
        return  sum(k > 0 and i + k in c or k == 0 and c[i] > 1 for i in c)

"""
class Solution:
    def findPairs(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        if k < 0: return 0
        lookup, res = set(), set()
        for i in nums:
            if i + k in lookup:
                res |= {i}
            if i- k in lookup:
                res |= {i-k}
            lookup |= {i}
        return len(res)


class Solution:
    def findPairs(self, nums, k):
        if k>0:
            return len(set(nums)&set(n+k for n in nums))
        elif k==0:
            sum(v>1 for v in collections.Counter(nums).values())
        else:
            return 0