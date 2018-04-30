"""
552. Student Attendance Record II
Given a positive integer n, return the number of all possible attendance records with length n, 
which will be regarded as rewardable. The answer may be very large, return it after mod 109 + 7.

A student attendance record is a string that only contains the following three characters:

'A' : Absent.
'L' : Late.
'P' : Present.
A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

Example 1:
Input: n = 2
Output: 8 
Explanation:
There are 8 records with length 2 will be regarded as rewardable:
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" won't be regarded as rewardable owing to more than one absent times. 
Note: The value of n won't exceed 100,000.


"""

"""

P 表示以P结尾的，
A 表示以A结尾的
L1 表示以L结尾
L2 表示以LL结尾
naP 表示以P结尾前面没有A，
naL1 表示以L结尾前面没有A 
naL2 表示以LL结尾前面没有A 


P = P + A + L1 + L2  比如 ...P,  ...A, ...L, ...LL, 新的以P结尾的是上一个结尾的和 变成 ...PP,  ...AP, ...LP, ...LLP
L2 = L1     现在L2就是上一个L1,结果 把....L 变成 ....LL
L1 = P + A   比如 ...P, ...A, 以一个L结尾的就是 ...PL, ...AL
A = naP  + naL1 + naL2 以A结尾必须前面没有出现过A, 


naL2 = naL1 现在naL2就是上一个naL1,结果 把....L 变成 ....LL
naL1 = naP 只能是上一个 没有出现A的以P结尾的append L 
naP = naP + naL1 + naL2  比如 ...P,  ...L, ...LL, 新的以naP结尾的是上一个结尾的和 变成 ...PP, ...LP, ...LLP


上面的等式：
P = P + A + L1 + L2 
L2 = L1 
L1 = P + A 


A(n) = naP(n-1)  + naL1(n-1) + naL2 (n-1)
naL2(n) = naL1(n-1) 
naL1(n) = naP(n-1)
naP(n) = naP(n-1) + naL1(n-1) + naL2(n-1) 

推出：
naP(n-1) = naP(n-2) + naL1(n-2) + naL2(n-2) = A(n-1)
naL1(n-1) = naP(n-2) = A(n-2)
naL2(n-1) = naL1(n-2) = naP(n-3) = A(n-3)


A(n) = A(n-1) + A(n-2) + A(n-3)

"""



class Solution:
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1: return 3
        M = 10**9 + 7
        P, A, L1, L2, naP, naL1, naL2 = 3, 2, 2, 1, 2, 1, 1
        for i in range(3, n+1):
            P, L1, A, L2, naP, naL1, naL2  = (P + A + L1 + L2)%M, \
                                             (P + A)%M, \
                                             (naP + naL1+naL2)%M, \
                                             L1,  \
                                             (naP + naL1 + naL2)%M, \
                                             naP, \
                                             naL1
                                               
        return (P+A+L1+L2)%M



class Solution:
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1: return 3
        if n == 2: return 8
        M = 10**9 + 7
        P, L1, L2, A, A1, A2 = 8, 5, 2, 4, 2, 1
        for i in range(3, n+1):
            P, L1, L2, A, A1, A2  = (A + L1 + L2 + P)%M, (A + P)%M, L1, (A+A1+A2)%M, A, A1
                                             
        return P


class Solution:
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        def Mul(A, B) :
            C = list(zip(*B))
            mod = 1000000007
            return [[sum(a * b for a, b in zip(row, col)) % mod
                     for col in C]
                    for row in A]

        def Pow(A, b) :
            N = len(A)
            C = [[0] * r + [1] + [0] * (N - r - 1) for r in range(N)]
            while b > 0 :
                if b % 2 == 1 :
                    C = Mul(C, A)
                A = Mul(A, A)
                b //= 2
            return C

        A = [[1, 1, 1, 0, 0, 0],
             [1, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 0, 0],
             [1, 1, 1, 1, 1, 1],
             [0, 0, 0, 1, 0, 0],
             [0, 0, 0, 0, 1, 0]];
        return Pow(A, n + 1)[3][0]


import numpy as np

class Solution(object):
    def checkRecord(self, n):
        """
        :type n: int
        :rtype: int
        """
        A = np.matrix([[0, 0, 1, 0, 0, 0],
                       [1, 0, 1, 0, 0, 0],
                       [0, 1, 1, 0, 0, 0],
                       [0, 0, 1, 0, 0, 1],
                       [0, 0, 1, 1, 0, 1],
                       [0, 0, 1, 0, 1, 1]])
        power = A
        mod = 10**9 + 7
        while n:
            if n & 1:
                power = (power * A) % mod
            A = A**2 % mod
            n //= 2
        return int(power[5, 2])