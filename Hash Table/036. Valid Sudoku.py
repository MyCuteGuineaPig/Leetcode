"""
36. Valid Sudoku

Example 1:

Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
Example 2:

Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

"""

class Solution:
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        vec = [set() for _ in range(27)]
        for i, V in enumerate(board):
            for j, v in enumerate(V):
                if v != '.':
                    if v in vec[i] or v in vec[j+9] or v in vec[18+ i//3*3 + j//3]:
                        return False
                    vec[i] |= {v}
                    vec[j+9] |= {v}
                    vec[18+ i//3*3 + j//3] |= {v}
        return True


# bit 
class Solution:
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        vec = [0]*27
        for i, V in enumerate(board):
            for j, v in enumerate(V):
                if v != '.':
                    ind = 1 << (ord(v) - ord('0'))
                    if vec[i] & ind or vec[j+9] & ind or vec[18+ i//3*3 + j//3] & ind:
                        return False
                    vec[i] |= ind
                    vec[j+9] |= ind
                    vec[18+ i//3*3 + j//3] |= ind
        return True


class Solution:
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        for i in range(9):
            if not self.isValidList([board[i][j] for j in range(9)]) or \
               not self.isValidList([board[j][i] for j in range(9)]):
                print("here")
                return False
        for i in range(3):
            for j in range(3):
                if not self.isValidList([board[m][n] for n in range(3 * j, 3 * j + 3) \
                                                     for m in range(3 * i, 3 * i + 3)]):
                    return False
        return True

    def isValidList(self, xs):
        xs = list(filter(lambda x: x != '.', xs))
        return len(set(xs)) == len(xs)
