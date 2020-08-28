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



class Solution:
    def matrixScore(self, A: List[List[int]]) -> int:
        for i in range(len(A)):
            if A[i][0] == 0:
                self.flip_row(A, i)
        return self.dfs(A, 1)

    def dfs(self, a, j):
        if j == len(a[0]):
            return sum([int(''.join(map(str, a[i])), 2) for i in range(len(a))])
        count = sum([1 for i in range(len(a)) if a[i][j]])
				
        if count < (len(a)+1)//2:
            self.flip_col(a, j)
        return self.dfs(a, j + 1)

    def flip_row(self, a, i):
        for j in range(len(a[0])):
            a[i][j] = int(not a[i][j])

    def flip_col(self, a, j):
        for i in range(len(a)):
            a[i][j] = int(not a[i][j])