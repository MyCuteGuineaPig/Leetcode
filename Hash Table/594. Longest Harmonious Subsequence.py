"""
594. Longest Harmonious Subsequence


We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
"""

class Solution:
    def findLHS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        dic = collections.Counter(nums)
        res = 0
        for i, v in dic.items():
            if i + 1 in dic:
                res = max(res, v + dic[i+1]);
        return res

class Solution:
    def findLHS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        dic = collections.defaultdict(int)
        res = 0
        for i in nums:
            dic[i]+=1
            if i + 1 in dic:
                res = max(res, dic[i] + dic[i+1])
            if i - 1 in dic:
                res = max(res, dic[i] + dic[i-1])
        return res