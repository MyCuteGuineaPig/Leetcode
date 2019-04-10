/*
37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

*/

//write by own
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<int>mp(243,0);
        for(int i = 0; i<board.size(); i++){
            for(int j = 0; j<board[i].size(); j++){
                if(board[i][j] == '.') continue;
                int cur = board[i][j] - '0'-1;
                mp[9*i+cur] = 1;
                mp[9*9 + 9*j + cur] = 1;
                mp[9*9*2 + (i/3*3+j/3)*9 + cur ] = 1;
            }
        }
        solve(board, mp, 0, 0);
           
    }
    
    bool solve(vector<vector<char>>&board, vector<int>&mp, int i, int j){
        if(j == 9){
            i = i+ 1; 
            j = 0;
        }
        if(i == 9){
            return true;
        }
        
        if(board[i][j]!='.') {
            if(solve(board,mp, i, j+1)) return true;
            else return false;
        }
        for(int x = 0; x<9; x++){
            if(!mp[9*i + x] && !mp[9*9 + j*9 + x] && !mp[9*9*2 + (i/3*3+j/3)*9 + x ]){
                mp[9*i+x] = 1;
                mp[9*9 + 9*j + x] = 1;
                mp[9*9*2 + (i/3*3+j/3)*9 + x ] = 1;
                if(solve(board,mp, i, j+1)){
                    board[i][j] = (x+1) + '0';
                    return true;
                }
                mp[9*i+x] = 0;
                mp[9*9 + 9*j + x] = 0;
                mp[9*9*2 + (i/3*3+j/3)*9 + x ] = 0;
            }
        }
        return false;
    }
};

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
