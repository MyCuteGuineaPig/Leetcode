"""
74. Search a 2D Matrix
"""

class Solution:
    def searchMatrix(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        if len(matrix)==0 or len(matrix[0])==0: return False
        m, n = len(matrix), len(matrix[0])
        l = 0;r = m*n-1
        while l<r:
            mid = (l+r)>>1
            if matrix[mid//n][mid%n]>=target:
                r = mid
            else: l = mid+1
        return True if target == matrix[l//n][l%n] else False


class Solution:
    def searchMatrix(self, matrix, target):
        if not bool(matrix) or not bool(matrix[0]): return False
        i = bisect.bisect_right(matrix, [target]) #i = bisect.bisect_left(matrix, [target]) aslo work
        if i < len(matrix) and matrix[i][0] == target:
            return True
        row = matrix[i-1]
        j = bisect.bisect_left(row, target)
        return j < len(row) and row[j] == target

class Solution:
    def searchMatrix(self, matrix, target):
        return bool(matrix) and target in matrix[bisect.bisect_left(matrix, [target+1])-1]


class Solution:
    def searchMatrix(self, matrix, target):
        m = bisect.bisect_left(matrix,[target+1])-1
        return bool(matrix) and bool(matrix[0]) and matrix[m][bisect.bisect_left(matrix[m],target+0.5)-1] == target #加0.5是防止超出范围 比如[[2]] 找1, bisect 返回1,但是没有matrix[0][1],只有[0][0]与其这样不如加个数然后再减去1
#或者用bisect.bisect_right


class Solution:
    def searchMatrix(self, matrix, target):
        m = bisect.bisect_left(matrix,[target+1])-1
        return bool(matrix) and bool(matrix[0]) and matrix[m][bisect.bisect_right(matrix[m],target)-1] == target 