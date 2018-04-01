/*
37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
        return;
    }
    
    bool helper(vector<vector<char>>& board, int row, int col){
        if(row == 9) return true;
        if(board[row][col] !='.'){
            if((col<8 && helper(board, row, col+1)) || ( col==8 && helper(board, row+1, 0)))
                return true;
        }
        else{
            for(int num = 1; num<=9; num++){
                if(checking(board,row,col,num)){
                    board[row][col] = num+'0';
                    if((col<8 && helper(board, row, col+1)) || ( col==8 && helper(board, row+1, 0)))
                        return true;
                    board[row][col] = '.';
                }
            }
        }
        return false;
    }
    
    bool checking(vector<vector<char>>& board, int i, int j, const int num){
        int row = i/3*3;
        int col = j/3*3;
        for(int m = 0; m<9; m++){
            if(board[i][m]!='.' && board[i][m]-'0' == num) {
                return false;
            }
            if(board[m][j]!='.' && board[m][j]-'0' == num) {
                return false;
            }
            if(board[row+m/3][col+m%3]!='.' && board[row+m/3][col+m%3] - '0' == num) {
                return false;
            }
        }
        return true;
    }
    
};



class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
    
    bool helper(vector<vector<char>>& board, int row, int col){
        if(row == 9) return true;
        if(col == 9) return helper(board, row+1, 0);
        if(board[row][col] !='.') return helper(board, row, col+1);
        else{
            for(int num = 1; num<=9; num++){
                if(checking(board,row,col,num)){
                    board[row][col] = num+'0';
                    if(helper(board, row, col+1))
                        return true;
                    board[row][col] = '.';
                }
            }
        }
        return false;
    }
    
    bool checking(vector<vector<char>>& board, int i, int j, const int num){
        int row = i/3*3;
        int col = j/3*3;
        for(int m = 0; m<9; m++){
            if(board[i][m]!='.' && board[i][m]-'0' == num)
                return false;
            if(board[m][j]!='.' && board[m][j]-'0' == num)
                return false;
            if(board[row+m/3][col+m%3]!='.' && board[row+m/3][col+m%3] - '0' == num)
                return false;
        }
        return true;
    }
    
};