class Solution:
    def luckyNumbers (self, matrix: List[List[int]]) -> List[int]:
        if len(matrix) == 0 or len(matrix[0]) == 0:
            return 0
        l = collections.defaultdict(int)
        n, m = len(matrix), len(matrix[0])
        def findMax(j):
            if j in l:
                return l[j]
            maxn = matrix[0][j]
            for i in range(1,n):
                if matrix[i][j] > maxn:
                        maxn = matrix[i][j] 
            l[j] = maxn
            return maxn
        res = []
        for r in matrix:
            minn = min(r)
            ind = r.index(minn)
            if findMax(ind) == minn:
                res.append(minn)
        return res

“”“
We can create a set of the minimum row values using set comprehension.
To create a set of the maximum column values we can use the unpacking operator (*) on the matrix 
        and use zip to iterate over the unpacked rows in parallel.
We can then get a set of our lucky numbers by intersecting those two sets using the intersection operator (&). 
    Then all that is left to do is to convert the set back into a list.

”“”

class Solution:
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:
        return list({min(row) for row in matrix} & {max(col) for col in zip(*matrix)})