/*
36. Valid Sudoku

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

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
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
The given board contain only digits 1-9 and the character '.'.
The given board size is always 9x9.


*/



class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>>lookup(27);
        for(int i = 0; i<9; i++){
            for(int j = 0; j<9; j++){
                if(board[i][j]!='.'){
                    if(lookup[i].count(board[i][j]) || lookup[j+9].count(board[i][j]) || lookup[18+j/3 + i/3*3].count(board[i][j])) return false;
                    lookup[i].insert(board[i][j]);
                    lookup[j+9].insert(board[i][j]);
                    lookup[18 + i/3*3 + j / 3].insert(board[i][j]);
                }
            }
        }
        return true;
    }
};


class Solution {
public:
   bool isValidSudoku(vector<vector<char>>& board) {
    vector<short> col(9, 0);
    vector<short> block(9, 0);
    vector<short> row(9, 0);
    for (int i = 0; i < 9; i++)
     for (int j = 0; j < 9; j++) {
         if (board[i][j] != '.') {
             int idx = 1 << (board[i][j] - '0');
             if (row[i] & idx || col[j] & idx || block[i/3 * 3 + j / 3] & idx)
                return false;
            row[i] |= idx;
            col[j] |= idx;
            block[i/3 * 3 + j/3] |= idx;
         }
     }
     return true;
  }
};


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
       
        int i,j,k,num;
        int rows[9][9]={0},cols[9][9]={0},box[9][9]={0};
        
        for(i=0;i<9;i++){
           for(j=0;j<9;j++){
                if(board[i][j] != '.'){
                    k = (i/3)*3+j/3;
                    num = board[i][j]-'1';
                    if((rows[i][num] == 1) || (cols[j][num] == 1) || (box[k][num] == 1)){
                        return false;
                    }
                    rows[i][num]  = cols[j][num]  =box[k][num]  =1;
                    
                }
           
           
           }    
        }
        return true;
        
        
    }
};