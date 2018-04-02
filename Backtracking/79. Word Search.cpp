/*
79. Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

*/


class Solution {
public:
    vector<pair<int,int>>dir;
    bool exist(vector<vector<char>>& board, string word) {
        dir = {{-1,0},{0,-1},{1,0},{0,1}};
        for(int i = 0; i<board.size();i++){
            for(int j = 0; j<board[0].size();j++){
                if(board[i][j] == word[0]){
                    vector<vector<int>>visited(board.size(),vector<int>(board[0].size(),0));
                    if( dfs(board,word,visited,i,j,1))
                        return true;
                }
            }
        }
        return false;
    }
    
    bool dfs(const vector<vector<char>>& board, const string& word,vector<vector<int>>& visited, int i, int j, int index){
        if(index == 1) visited[i][j] = 1;
        if(index == word.size()) return true;
        for(int k = 0; k<4; k++){
            int x = i + dir[k].first;
            int y = j + dir[k].second;
            if(x>=0 && x<board.size() && y>=0 && y<board[0].size() && visited[x][y] == 0 && board[x][y]==word[index]){
                visited[x][y] = 1;
                if(dfs(board,word,visited,x,y,index+1)) return true;
                visited[x][y] = 0;
            }
        }
        return false;
    }
};




/*
用bitmask的
 board[x][y] ^= 128;
 取非后不是英文字母了

*/
class Solution {
public:
    bool exist(vector <vector<char>> &board, string word) {
        const int m = board.size();
        const int n = board[0].size();
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (exist(board, x, y, word, 0))
                    return true;
            }
        }
        return false;
    }

private:
    bool exist(vector <vector<char>> &board, int x, int y, const string &word, int step) {
        if (step == word.size())
            return true;
        if (x < 0 || y < 0 || x == board.size() || y == board[0].size() || board[x][y] != word[step])
            return false;
        board[x][y] ^= 128; // visited flag, the size of char in C++ is 1 byte, and the highest bit of all the ASCII of alphabets is 0.
        bool existFlag = exist(board, x, y + 1, word, step + 1) || exist(board, x + 1, y, word, step + 1) ||
                         exist(board, x - 1, y, word, step + 1) || exist(board, x, y - 1, word, step + 1);
        board[x][y] ^= 128;
        return existFlag;
    }
};