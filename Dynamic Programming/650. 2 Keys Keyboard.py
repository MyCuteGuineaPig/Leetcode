"""
650. 2 Keys Keyboard

18/2 = 9 Copy 9 'A’s 2 times (2)
9/3=3 Copy 3 'A’s 3 times (3)
3/3=1 Copy 1’A’s 3 times (3)
Answer: 2+3+3= 8

必须是最大的number

比如 18 % 9 = 2  
复制二9回，但是复制2 = 2 + 9 = 11， 而不是最小的8个


"""

class Solution:
    def minSteps(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [0,]*(n+1)
        for i in range(2,n+1):
            dp[i] = i
            for j in range(2, int(i**0.5)+1):
                if i%j == 0:
                    dp[i] = dp[i//j]+j
                    break
        return dp[n]

class Solution:
    def minSteps(self, n):
        """
        :type n: int
        :rtype: int
        """
        res = 0
        for i in range(2, int(n**0.5)+1):
            while n%i == 0:
                res += i
                n = n//i
        return res + n*(n>1)






# Integer Factorization
class Solution:
    def minSteps(self, n: int) -> int:
        if n == 1: return 0
        for i in range(2, n+1):
            if n % i == 0:
                return self.minSteps(n // i) + i

class Solution:
    def minSteps(self, n):
        """
        :type n: int
        :rtype: int
        """
        def dfs(n):
            res = 0
            d = 2 
            while d*d <= n:
                while n% d == 0:
                    n /= d
                    yield d
                d += 1
            if n > 1:
                yield n 
        return int(sum(dfs(n)))

"""
32ms

"""
class Solution:
    def minSteps(self, n):
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
        ret = 0
        for p in primes:
            while not (n % p):
                n /= p
                ret += p
        return int(ret + n * (n > 1))

"""
40
"""
class Solution:
    def minSteps(self, n):
        """
        :type n: int
        :rtype: int
        """
        def factors(n):
            d = 2
            while d * d <= n:
                while n % d == 0:
                    n /= d
                    yield d
                d += 1
            if n > 1:
                yield n

        return int(sum(factors(n)))
            