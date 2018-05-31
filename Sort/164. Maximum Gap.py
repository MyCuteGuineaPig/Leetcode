"""
164. Maximum Gap

Example 1:

Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.

"""
class Solution:
    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)<=1 : return 0
        min_, max_, n = min(nums), max(nums), len(nums)
        if max_ == min_: return 0
        maxl = [float('-inf'),]*n
        minl = [float('inf'),]*n
        length = (max_ - min_)/(n-1)
        for i in nums:
            index = int((i-min_)/length)
            maxl[index] = max(maxl[index],i)
            minl[index] = min(minl[index],i)
        res, prev = 0, maxl[0]
        for i in range(1,n):
            if minl[i] == float("inf"): continue
            res = max(minl[i]-prev,res)
            prev = maxl[i]
        return res

"""
radix sort
O(nlog10(k)) k is the largest number in nums
"""
class Solution:
    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)<=1 : return 0
        max_, n = max(nums), len(nums)
        exp, base = 1, 16
        aux = [0,]*n
        while max_//exp>0:
            count = [0,]*base
            for i in nums:
                count[(i//exp)%base]+=1
            
            for i in range(1,base):
                count[i] += count[i-1]

            for i in nums[::-1]:
                count[(i//exp)%base]-=1
                aux[count[(i//exp)%base]] = i
            exp *= base
            nums = aux

        res = 0 
        for i in range(1,n):
            res = max(nums[i]-nums[i-1],res)
        return res


class Solution:
    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 2:
            return 0
        # Radix sort
        exp = 1
        max_num = max(nums)
        while max_num // exp > 0:
            count = [0] * 10
            aux = [None] * len(nums)
            for num in nums:
                count[(num//exp)%10] += 1
            for i in range(1,10):
                count[i] += count[i-1]
            for num in nums[::-1]:
                idx = (num//exp)% 10
                count[idx] -= 1
                aux[count[idx]] = num
            nums = aux
            exp *= 10

        max_gap = 0
        for i in range(1, len(nums)):
            max_gap = max(max_gap, nums[i]-nums[i-1])
        return max_gap
        