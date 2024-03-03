/*
529. Minesweeper

Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 
'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, 
digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), 
return the board after revealing this position according to the following rules:

If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') 
    and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square ('E') with at least one adjacent mine is revealed, 
    then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.

*/




class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board[click[0]][click[1]] == 'M'){
            board[click[0]][click[1]] = 'X';
        }
        else{
            reveal(board, click[0], click[1]);
        }
        return board;
    }
    
    vector<pair<int,int>>direction =  {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1},{1,-1}, {1,0}, {1,1}};
    
    void reveal(vector<vector<char>>& board, int i, int j){
        int mines = 0;
        for(auto dir: direction){
            int x = dir.first + i, y = dir.second + j;
            if(x<0 || x>= board.size() || y<0 || y>= board[0].size()) continue;
            if (board[x][y] == 'M') mines++;
        }
        if (mines>0) board[i][j] = '0' + mines;
        else{
            board[i][j] = 'B';
            for(auto dir: direction){
                int x = dir.first + i, y = dir.second + j;
                if(x<0 || x>= board.size() || y<0 || y>= board[0].size()) continue;
                if (board[x][y] == 'E') reveal(board, x, y);
            }
        }
    }
};


//BFS


// Time:  O(m * n)
// Space: O(m + n)

class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)  {
        queue<vector<int>> q;
        q.emplace(click);
        while (!q.empty()) {
            int row = q.front()[0], col = q.front()[1];
            q.pop();
            if (board[row][col] == 'M') {
                board[row][col] = 'X';
            } else {
                int count = 0;
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        int r = row + i, c = col + j;
                        if (r < 0 || r >= board.size() || c < 0 || c < 0 || c >= board[r].size()) {
                            continue;
                        }
                        if (board[r][c] == 'M' || board[r][c] == 'X') {
                            ++count;
                        }
                    }
                }
                
                if (count > 0) {
                    board[row][col] = count + '0';
                } else {
                    board[row][col] = 'B';
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            if (i == 0 && j == 0) {
                                continue;
                            }
                            int r = row + i, c = col + j;
                            if (r < 0 || r >= board.size() || c < 0 || c < 0 || c >= board[r].size()) {
                                continue;
                            }
                            if (board[r][c] == 'E') {
                                vector<int> next_click = {r, c};
                                q.emplace(next_click);
                                board[r][c] = 'B';
                            }
                        }
                    }
                }
            }
        }
        
        return board;
    }
};