"""
Explanation
Two pattern for each row, 121 and 123.
121, the first color same as the third in a row.
123, one row has three different colors.

We consider the state of the first row,
pattern 121: 121, 131, 212, 232, 313, 323.
pattern 123: 123, 132, 213, 231, 312, 321.
So we initialize a121 = 6, a123 = 6.

We consider the next possible for each pattern:
Patter 121 can be followed by: 212, 213, 232, 312, 313
Patter 123 can be followed by: 212, 231, 312, 232

121 => three 121, two 123
123 => two 121, two 123

So we can write this dynamic programming transform equation:
b121 = a121 * 3 + a123 * 2
b123 = a121 * 2 + a123 * 2

We calculate the result iteratively
and finally return the sum of both pattern a121 + a123


Complexity
Time O(N), Space O(1)
Of course, we can do better.
O(logN) Time Solution

Well, I don't think it's required,
But still you can mention during interview,
(as a ciper code hinting that you are my follower).

"""


class Solution:
    def numOfWays(self, n):
        a121, a123, mod = 6, 6, 10**9 + 7
        for i in range(n - 1):
            a121, a123 = a121 * 3 + a123 * 2, a121 * 2 + a123 * 2
        return (a121 + a123) % mod


class Solution:
    def numOfWays(self, n: int) -> int:
        MOD = 1000000007
        P = ['ryr', 'yry', 'gry', 'ryg', 'yrg', 'grg', 'rgr', 'ygr', 'gyr', 'rgy', 'ygy', 'gyg']
        nei = [[i for i, x in enumerate(P) if all(a != b for a, b in zip(x, p))] for p in P]
        
        dp = [1] * 12
        for i in range(n - 1):
            dp = [sum(dp[j] for j in nei[i]) % MOD for i in range(12)]
        return sum(dp) % MOD



# Time:  O(logn)
# Space: O(1)
class Solution:
    def numOfWays(self, n):
        """
        :type n: int
        :rtype: int
        """
        def matrix_expo(A, K):
            result = [[1 if i == j else 0 for j in range(len(A))]
                       for i in range(len(A))]
            while K:
                if K % 2:
                    result = matrix_mult(result, A)
                    
                A = matrix_mult(A, A)
                K //= 2
            return result

        def matrix_mult(A, B):
            ZB = list(zip(*B)) #没有list 只能generate 一回，对于第二行之后for col in ZB 失效
            return [[sum(a*b % MOD for a, b in zip(row, col)) % MOD
                     for col in ZB] for row in A]
        
        MOD = 10**9 + 7
        T = [[3, 2],
             [2, 2]]
        return sum(matrix_mult([[6, 6]], matrix_expo(T, n-1))[0]) % MOD  # [a1, a0] * T^(n-1)
                    