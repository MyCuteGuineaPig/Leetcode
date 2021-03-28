"""
Having n PrimeNumbers:

can split it to two parts: like 4 -> 2*2, 5 -> 2*3, 6 -> 3*3 and so on. 
Moreover, if we have 2, 2, 2, it is always better to replace it to 3, 3. 

So in the end: optimal configuration has only 2 and 3 and number of 2 is not more than two. 

if n % 3 == 0: divide prime to all groups of Three e.g. if n = 6, like [2,2,2], [5,5,5]

if n>3 and  n % 3 == 1: divide prime to all groups of Three and one Four e.g. if n = 7, like [2,2,2], [5,5,5,5]

if n>3 and  n % 3 == 2: divide prime to all groups of Three and one Two e.g. if n = 5, like [2,2,2], [5,5]

"""


class Solution:
    def maxNiceDivisors(self, n: int) -> int:
        M = 10**9 + 7
        if n <= 3: return n
        if n % 3 == 0: return pow(3, n//3, M)
        if n % 3 == 1: return (pow(3, (n-4)//3, M) * 4) % M
        return (2*pow(3, n//3, M)) % M