"""
456. 132 Pattern


Example 1:
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]

Output: True

Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
"""

class Solution:
    def find132pattern(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        stk, secLarge = [], float('-inf')
        for i in nums[::-1]:
            if i < secLarge: return True
            while stk and stk[-1]  < i:
                secLarge = max(secLarge, stk.pop())
            stk.append(i)
        return False

class Solution:
    def find132pattern(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        stk, secLarge = [], float('-inf')
        for i in nums[::-1]:
            if i < secLarge: return True
            while stk and stk[-1]  < i:
                secLarge = stk.pop()
            stk.append(i)
        return False
    
 
#Descending Stack, minv 
 class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        if not nums:
            return False
        minv = nums[0]
        stk = []
        for i in nums[1:]:
            if i <= minv:
                minv = i
            else:
                while stk and i > stk[-1][0]:
                    if i < stk[-1][1]:
                        return True
                    else: stk.pop()
                stk.append([minv, i])
        return False   
