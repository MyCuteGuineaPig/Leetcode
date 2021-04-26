class Solution:
    def sumBase(self, n: int, k: int) -> int:
        sm = 0
        while n > 0:
            sm += n % k
            n //= k
        return sm