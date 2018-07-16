"""
477. Total Hamming Distance

Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
"""

class Solution:
    def totalHammingDistance(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        res = 0
        for i in range(32):
            li = [0, 0]
            for j in nums:
                bit = j >> i & 1
                li[bit] += 1
            res += li[1]*li[0]
        return res

class Solution:
    def totalHammingDistance(self, nums):
        return sum(b.count('0') * b.count('1') for b in zip(*map('{:032b}'.format, nums)))
#The * unpacks the list to individual arguments, so zip(*['0100','1110','0010']) is like zip('0100','1110','0010').
"""
zip(['0100','1110','0010'])
[('0100',), ('1110',), ('0010',)]

zip(*['0100','1110','0010'])
[('0', '1', '0'), ('1', '1', '0'), ('0', '1', '1'), ('0', '0', '0')]


"""