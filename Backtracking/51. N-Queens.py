"""
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

"""

"""
In this problem, whenever a location (x, y) is occupied, any other locations (p, q ) 
where p + q == x + y or p - q == x - y would be invalid. 
We can use this information to keep track of the indicators (xy_dif and xy_sum ) of the invalid positions
 and then call DFS recursively with valid positions only. 


At the end, we convert the result (a list of lists; each sublist is the indices of the queens) into the desire format.

"""

class Solution:
    def solveNQueens(self, n):
        def DFS(queens, xy_dif, xy_sum):
            p = len(queens)
            if p==n:
                result.append(queens)
                return None
            for q in range(n):
                if q not in queens and p-q not in xy_dif and p+q not in xy_sum: 
                    DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])  
    result = []
    DFS([],[],[])
    return [ ["."*i + "Q" + "."*(n-i-1) for i in sol] for sol in result]
        
    

    
    
#2020
class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        col = [0 for _ in range(n)]
        dia1, dia2 = [0 for _ in range(2*n-1)], [0 for _ in range(2*n-1)]
        res = []
        def dfs(cur, i):
            if i == n:
                res.append(cur)
                return 
            if i < n:
                for j in range (n):
                    if isValid(i, j):
                        assign(i,j,1)
                        dfs(cur + ['.'*j + 'Q' + '.'*(n-j-1)], i+1)
                        assign(i, j, 0)
        
        def isValid(i, j):
            return not (col[j] or dia1[n-1+i-j] or dia2[i+j])
        
        def assign(i, j, val):
            col[j] = val
            dia1[n-1+i-j] = val 
            dia2[i+j] = val
        dfs([], 0)
        return res
