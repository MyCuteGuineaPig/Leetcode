"""
861. Score After Flipping Matrix

We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.

"""

class Solution:
    def matrixScore(self, A):
        """
        :type A: List[List[int]]
        :rtype: int
        """
        if not A or not A[0]: return 0
        n, m = len(A), len(A[0])
        tot = n*2**(m-1)
        for i in range(1, m):
            zero = sum(A[j][0]^A[j][i] for j in range(n))
            tot += max(zero, n-zero)*2**(m-i-1)
        return tot



class Solution:
    def matrixScore(self, A):
        if not A or not A[0]: return 0
        n, m = len(A), len(A[0])
        tot = 0
        for i in range(m):
            zero = sum(A[j][0]^A[j][i] for j in range(n))
            tot += max(zero, n-zero)*2**(m-i-1)
        return tot

class Solution:
    def matrixScore(self, A):
        """
        :type A: List[List[int]]
        :rtype: int
        """
        M = len(A)
        N = len(A[0])
        res = M << (N - 1)
        for j in range(1, N):
            m = sum(A[i][j] == A[i][0] for i in range(M))
            res += max(m, M - m) <<(N - 1 - j)
        return res