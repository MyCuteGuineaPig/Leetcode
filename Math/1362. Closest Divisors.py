class Solution:
    def closestDivisors(self, num: int) -> List[int]:
        def largest(n):
            res = [1, n]
            for i in range(2, int(n**0.5)+1):
                if n % i == 0:
                    res = [i, n//i]
            return res
        r1, r2 = largest(num+1)
        r3, r4 = largest(num+2)
        return [r1, r2] if abs(r1 - r2) < abs(r3- r4) else [r3,r4]


class Solution:
    def closestDivisors(self, x):
        for a in range(int((x + 2)**0.5), 0, -1):
            if (x + 1) % a == 0:
                return [a, (x + 1) // a]
            if (x + 2) % a == 0:
                return [a, (x + 2) // a]


class Solution:
    def closestDivisors(self, x):
        return next([a, y // a] for a in range(int((x + 2)**0.5), 0, -1) for y in [x + 1, x + 2] if not y % a)