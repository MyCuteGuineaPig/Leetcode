class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        row, col, diag = [0 for _ in range(9)],  [0 for _ in range(9)],  [0 for _ in range(9)]
        for i, r in enumerate(board):
            for j, v in enumerate(r):
                if v != '.':
                    row[i] |= 1 << int(v) 
                    col[j] |= 1 << int(v)
                    diag[i//3*3 + j//3] |= 1 << int(v) 


        def move(i, j):
            print(i, j)
            if i == 9 and j == 0:
                return True 
            if j == 9:
                return move(i+1, 0)
            if board[i][j] != '.':
                return move(i, j+1)
            for val in range(1,10):
                if isValid(i, j, val):
                    row[i] |= 1 << val 
                    col[j] |= 1 << val 
                    diag[i//3*3 + j//3] |= 1 << val 
                    if move(i, j+1):
                        board[i][j] = str(val)
                        return True 
                    row[i] &= ~(1 << val)
                    col[j] &=  ~(1 << val)
                    diag[i//3*3 + j//3] &=  ~(1 << val)
            return False 
    
        def isValid(i, j, val):
            return not(row[i] & 1<<val  or col[j] & 1 << val or diag[i//3*3 + j//3] & 1 << val)
        move(0,0)
