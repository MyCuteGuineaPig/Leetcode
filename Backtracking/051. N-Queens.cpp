/*
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:


*/
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>>ans;
        vector<string> board(n, string(n, '.'));
        helper(ans,board,0,n);
        return ans;
    }
    
    void helper(vector<vector<string>>&ans, vector<string>& board, int row, int n){
        if(row==n){
            ans.push_back(board);
            return;
        }
        for(int i = 0; i<n; i++){
            if(check(row,i,board)){
                board[row][i]='Q';
                helper(ans,board,row+1,n);
                board[row][i] = '.';
            }
        }
        
    }
    
    bool check(int row, int col,vector<string>& board){
        /*
        只需要检查这一列，45 degree 和 135 degree 有没有一样的，
        不用检查每一行，和一行下方的
        */
        for(int i =0; i<board.size();i++) if (board[i][col] == 'Q') return false;
        for(int i =0; row-i>=0 && col-i>=0; i++) if (board[row-i][col-i] == 'Q') return false;
        for(int i =0; row-i>=0 && col+i <board.size(); i++) if (board[row-i][col+i] == 'Q') return false;
        return true;
    }
};

/*

The number of columns is n, the number of 45° diagonals is 2 * n - 1, the number of 135° diagonals is also 2 * n - 1. 
When reach [row, col], the column No. is col, the 45° diagonal No. is row + col and the 135° diagonal No. is n - 1 + col - row. 
We can use three arrays to indicate if the column or the diagonal had a queen before, if not, we can put a queen in this position and continue.

But we actually do not need to use three arrays, we just need one.
Now, when reach [row, col], the subscript of column is col, the subscript of 45° diagonal is n + row + col and the subscript of 135° diagonal is n + 2 * n - 1 + n - 1 + col - row.
*/


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>>ans;
        vector<string> board(n, string(n, '.'));
        vector<int>visited(5*n-2, 1);
        helper(ans,board,visited,0,n);
        return ans;
    }
    
    void helper(vector<vector<string>>&ans, vector<string>& board,vector<int>& visited, int row, int n){
        if(row==n){
            ans.push_back(board);
            return;
        }
        for(int i = 0; i<n; i++){
            if(visited[i] && visited[n+i+row] && visited[3*n-1+n-1+i-row]){
                visited[i] = visited[n+i+row] = visited[3*n-1+n-1+i-row] = 0;
                board[row][i]='Q';
                helper(ans,board,visited,row+1,n);
                board[row][i] = '.';
                visited[i] = visited[n+i+row] = visited[3*n-1+n-1+i-row] = 1;
            }
        }
    }
};





class Solution {
public:
    void backtrack(vector<vector<string>>& res, vector<string>& cur, int row, int n, vector<int>&vertical, vector<int>&diag1, vector<int>&diag2){
        if (row == n){
            res.push_back(cur);
            return;
        }
        string tmp(n, '.');
        cur.push_back(tmp);
        for(int i = 0; i < n; ++i){
            if(vertical[i] || diag1[i-row + n-1] ||   diag2[row + i]) continue;
            vertical[i] = 1;
            diag1[i-row + n-1] = 1;
            diag2[row + i] = 1;
            cur.back()[i] = 'Q';
            backtrack(res, cur, row+1, n, vertical, diag1, diag2);
            cur.back()[i] = '.';
            vertical[i] = 0;
            diag1[i-row + n-1] = 0;
            diag2[row + i] = 0;
        }
        cur.pop_back();
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<int>vertical(n);
        vector<int>diag1(2*n-1);
        vector<int>diag2(2*n-1);
        vector<vector<string>> res;
        vector<string> cur;

        backtrack(res, cur, 0,  n, vertical, diag1, diag2);

        return res;
    }
};