/*
289. Game of Life

According to the Wikipedia's article: "The Game of Life, also known simply as Life, 
is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). 
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules 
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state. 
The next state is created by applying the above rules simultaneously to every cell in the current state, 
where births and deaths occur simultaneously.

Example:

Input: 
[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]
Output: 
[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]
Follow up:

Could you solve it in-place? Remember that the board needs to be updated at the same time: 
You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, 
which would cause problems when the active area encroaches the border of the array. How would you address these problems?

*/


/*

先变化matrix到想要的格式, 然后再做transform到结果: 

count 周围8个点 + 现在点， 把下个generation alive的cell |= 2, 

count == 4 && board[i][j] == 1 表示现在点为1，周围三个邻居为1
count == 3, 现在cell自己是0， 但周围邻居有三个alive， or 自己是1， 周围邻居有两个是alive

最后再把matrix 每个cell, matrix[i][j]>>=2, 把下代alive的赋值成1

*/
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                
                int count = 0;
                for(int I = max(i-1, 0); I<=min(i+1, n-1); I++){
                    for(int J = max(j-1, 0); J<=min(j+1, m-1); J++){
                        count+= board[I][J] & 1;
                    }
                }
                
                if((count == 4 && board[i][j] == 1)|| count==3) 
                    //count == 4 && board[i][j] == 1 周围有三个neighbour的
                    //count==3, 自己是0， 周围邻居有三个， or 自己是1， 周围邻居有两个
                    board[i][j] |= 2;
                
            }
        }
        
        for(auto & b: board)  for(auto & n: b)  n >>= 1;   
    }
};


/*
状态: 前一位表示下一代的状态,后一位表示当前的状态
00: 死->死
10: 死->活
01: 活->死
11: 活->活

*/
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        if (m == 0) return;
        vector<vector<int>> dir = {{1,-1},{1,0},{1,1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1}};
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = 0;
                for (int k = 0; k < 8; k++) {
                    int r = i + dir[k][0];
                    int c = j + dir[k][1];
                    if (r < 0 || r >= m || c < 0 || c >= n) continue;
                    cnt += board[r][c] & 1;
                }
                if (cnt == 3 || ((board[i][j] & 1) && cnt == 2)) board[i][j] |= 2;
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) 
                board[i][j] = board[i][j] >> 1;
        }
    }
};