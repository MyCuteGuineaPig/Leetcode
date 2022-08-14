class Solution:
    def minOperations(self, A: List[int], numsDivide: List[int]) -> int:
        g = gcd(*numsDivide)
        return next((i for i,a in enumerate(sorted(A)) if g % a == 0), -1)

class Solution:
    def minOperations(self, A: List[int], numsDivide: List[int]) -> int:
        g = gcd(*numsDivide)
        for i,a in enumerate(sorted(A)):
            if g % a == 0: return i
            if a > g: break
        return -1


# O(N)
class Solution:
    def minOperations(self, A: List[int], numsDivide: List[int]) -> int:
        g = gcd(*numsDivide)
        small = min((a for a in A if g % a == 0), default = 0)
        return sum(a < small for a in A) if small else -1


class Solution:
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:
        div = reduce(gcd, numsDivide)
        min_n = min(filter(lambda x: div % x == 0, nums), default = -1)
        return -1 if min_n == -1 else sum(n < min_n for n in nums)