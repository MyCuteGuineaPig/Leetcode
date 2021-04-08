class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res = []
        dirr = {'right':[0,1],'down':[1,0], 'left':[0,-1], 'up':[-1,0]}
        nxt = {'right':'down','down':'left','left':'up','up':'right'}
        m, n = len(matrix), len(matrix[0])
        def walk(i, j, d):
            res.append(matrix[i][j])
            matrix[i][j] = 1000
            if len(res) == m*n:
                return 
            a, b = i + dirr[d][0], j + dirr[d][1]
            if 0 <= a < m and 0 <= b < n and matrix[a][b]!=1000:
                walk(a, b, d)
            else:
                d = nxt[d]
                a, b = i + dirr[d][0], j + dirr[d][1]
                walk(a,b,d)
        walk(0,0,'right')
        return res

""""
    |1 2 3|      |6 9|      |8 7|      |4|  =>  |5|  =>  ||
    |4 5 6|  =>  |5 8|  =>  |5 4|  =>  |5|
    |7 8 9|      |4 7|

 [*matrix.pop(0)]: 因为之后的matrix 变成tuple 

 [*zip(*matrix))] 是 [(1,4,7), (2,5,8),(3,6,9)]
  [*zip(*matrix))][::-1] 是 [(3,6,9), (2,5,8),(1,4,7)]
"""

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        return matrix and [*matrix.pop(0)] + self.spiralOrder([*zip(*matrix)][::-1])
