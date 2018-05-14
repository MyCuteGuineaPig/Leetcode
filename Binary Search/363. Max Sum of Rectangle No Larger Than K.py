"""
363. Max Sum of Rectangle No Larger Than K

Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Given matrix = [
  [1,  0, 1],
  [0, -2, 3]
]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
Credits:

"""
"""
用bisect.insort_left()否则有tle
"""

class Solution:
    def maxSumSubmatrix(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        m, n = len(matrix), len(matrix[0])
        res = -10**10
        if m>n:
            m, n = n, m #make m always smallest
        for si in range(m):
            li = [0,]*n
            for i in range(si,m):
                for j in range(n):
                    li[j] +=  matrix[i][j] if m == len(matrix) else matrix[j][i]
                s = [0]
                sumval = 0
                for num in li:
                    sumval += num
                    i = bisect.bisect_left(s,sumval-k)
                    if i<len(s):
                        res = max(res, sumval-s[i])
                    bisect.insort(s,sumval)
        return res
