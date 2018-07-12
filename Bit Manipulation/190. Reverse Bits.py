"""
190. Reverse Bits

Input: 43261596
Output: 964176192
Explanation: 43261596 represented in binary as 00000010100101000001111010011100, 
             return 964176192 represented in binary as 00111001011110000010100101000000.
"""
class Solution:
    # @param n, an integer
    # @return an integer
    def reverseBits(self, n):
        res = 0
        for i in range(32):
            res <<= 1
            res |= (n &1)
            n >>= 1
        return res

class Solution:
    # @param n, an integer
    # @return an integer
    def reverseBits(self, n):
        oribin='{0:032b}'.format(n)
        reversebin=oribin[::-1]
        return int(reversebin,2)


def reverseBits(self, n):
    return int(bin(n)[2:].zfill(32)[::-1], 2)#补上0