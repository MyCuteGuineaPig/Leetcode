"""
868. Binary Gap

"""


class Solution:
    def binaryGap(self, N):
        """
        :type N: int
        :rtype: int
        """
        res, d = 0, -32
        while N:
            if N & 1:
                res, d = max(res, d), 0
            d += 1
            N >>= 1
        return res
                
class Solution:
    def binaryGap(self, N):
        temp = [i for i, v in enumerate(bin(N)) if v == '1']
        return max([w-i for i, w in zip(temp,temp[1:])],default = 0)