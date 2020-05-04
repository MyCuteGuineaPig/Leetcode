class Solution:
    def findComplement(self, num: int) -> int:
        res =i = 0
        while num:
            if not num & 1:
                res |= 1 << i
            num = num >> 1
            i += 1
        return res

class Solution:
    def findComplement(self, num: int) -> int:
        i = 1
        while i <= num:
            i = i << 1
        return (i - 1) ^ num

class Solution:
    def findComplement(self, num: int) -> int:
        copy = num;
        i = 0;

        while copy != 0 :
            copy >>= 1;
            num ^= (1<<i);
            i += 1;
        return num;

class Solution:
    def findComplement(self, num: int) -> int:
        mask = 1
        while( mask < num):
            mask = (mask << 1) | 1
        return ~num & mask

class Solution:
    def findComplement(self, num: int) -> int:
        n = 0;
        while (n < num):
            n = (n << 1) | 1;
        return n - num;