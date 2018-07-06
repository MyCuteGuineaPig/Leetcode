"""
204. Count Primes

Count the number of prime numbers less than a non-negative number, n.

Example:

Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

"""
import math
class Solution:
    def countPrimes(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <=2: return 0
        st, count, ceil = [0]*n, 1, math.floor(n**0.5)+1
        for i in range(3,n,2):
            if st[i] == 0:
                count += 1
                for j in range(i*i,n, i*2):
                    st[j] = 1
        return count


import math
class Solution:
    def countPrimes(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <=2: return 0
        st, count, ceil = [0]*n, n//2, math.floor(n**0.5)+1
        for i in range(3,ceil,2):
            if st[i] == 0:
                for j in range(i*i,n, i*2):
                    if not st[j]:
                        count -= 1               
                        st[j] = 1
        return count


class Solution:
    def countPrimes(self, n):
        if n <=2: return 0
        st,ceil = [1]*n, int(n**0.5)+1
        st[0:2] = [0]*2
        st[4: n: 2] = [0]*len(st[4: n: 2])
        for i in range(3,ceil,2):
            if st[i]:
                st[i*i: n: i] = [0]*len(st[i*i: n: i])
        return sum(st)