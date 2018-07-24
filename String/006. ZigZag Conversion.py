"""

6. ZigZag Conversion


Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

"""
import functools
class Solution:
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if len(s) <= numRows or numRows == 1: return s
        li = [[]for _ in range(numRows)]
        j, dir = 0, -1 
        for v in s:
            if j == 0 or j == numRows - 1:
                dir *= -1
            li[j].append(v)
            j+=dir
        return functools.reduce(lambda x, y: x + "".join(y), li,"")


class Solution:
    def convert(self, s, numRows):
        if len(s) <= numRows or numRows == 1: return s
        step = 2*numRows - 2
        res = ""
        for i in range(numRows):
            for j in range(0, len(s)-i, step):
                res += s[i+j]
                if i > 0 and i < numRows - 1 and i + j + step - 2*i < len(s):
                    res += s[ i + j + step - 2*i ]
        return res