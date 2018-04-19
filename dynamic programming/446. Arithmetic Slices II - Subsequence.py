"""
446. Arithmetic Slices II - Subsequence
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.

A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.

The function should return the number of arithmetic subsequence slices in the array A.

The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.


Example:

Input: [2, 4, 6, 8, 10]

Output: 7

Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

"""
import collections
class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic, res = [collections.defaultdict(int) for _ in range(len(A))] , 0
        for i in range(1, len(A)):
            for j in range(0,i):
                res += dic[j][A[i] - A[j]]
                dic[i][A[i] - A[j]] += dic[j][A[i] - A[j]]+1 # 是加上比如[2,2,3,4] 如果不是+， return是1
        return res

"""
上面的解不efficient 
因为很有可能j 中 没有A[i] - A[j], 所以就会创建很多key，然后得到default value是0
与其创造很多key，不如先判断有没有key，
下面比上面的速度快1倍，

"""

import collections
class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic, res = [collections.defaultdict(int) for _ in range(len(A))] , 0
        for i in range(1, len(A)):
            for j in range(i):
                dic[i][A[i] - A[j]] += 1  
                if A[i] - A[j] in dic[j]:  # efficient
                    res += dic[j][A[i] - A[j]]
                    dic[i][A[i] - A[j]] += dic[j][A[i] - A[j]] # 是加上比如[2,2,3,4] 如果不是+， return是1
        return res




class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic={}
        for i in range(len(A)):
            if A[i] in dic:
                dic[A[i]].append(i)
            else:
                dic[A[i]]=[i]
        dp=[{} for _ in range(len(A))]
        for i in range(len(A)):
            for j in range(i):
                t=A[i]-A[j]
                x=A[j]-t
                if x in dic:
                    for k in dic[x]:
                        if k<j:
                            dp[i][t]=dp[i].get(t,0)+1
                if t in dp[j]:
                    dp[i][t]=dp[i].get(t,0)+dp[j][t]
        s=0
        for x in dp:
            for i in x:
                s+=x[i]
        return s