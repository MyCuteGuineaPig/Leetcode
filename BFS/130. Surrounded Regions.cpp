/*
130. Surrounded Regions.cpp

Time	    Space	    Difficulty	
O(m * n)	O(m + n)	Medium

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X


basic idea: 要是边界出发的店，肯定不行，从每个边界出发，bfs，如果没有被bfs弄上的点，不是临近边界的店
注意：
    board[i][j-1]='1'; 必须在if里面，因为如果在外面的话，会有runtime error，下一个while check 一个本来上一个if应该把O变得，但结果push 进queue，因为之前没有变1


*/


class Solution {
public:
    int n,m;

    void solve(vector<vector<char>>& board) {
        n = board.size();
        if(n==0) return;
        m = board[0].size();
        if(m==0) return;
        
        for(int i = 0; i<n; i++){
            if(board[i][0]=='O')
                BFS(board,i,0);
            if(board[i][m-1]=='O')
                BFS(board,i,m-1);
        }


        for(int j = 0; j<m; j++){
            if(board[0][j]=='O')
                BFS(board,0,j);
            if(board[n-1][j]=='O')
                BFS(board,n-1,j);
                
        }

        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                if(board[i][j]=='O')
                    board[i][j]='X';
                else if(board[i][j]=='1')
                    board[i][j]='O';
            }
        }

    }

    void BFS(vector<vector<char>>& board, int i, int j){
        queue<pair<int,int>>q;
        q.push(make_pair(i,j));
        board[i][j]='1';
        while(q.size()){
            pair<int,int>top = q.front();
            q.pop();
            int i = top.first;
            int j = top.second;
            if( j-1 >= 0 && board[i][j-1]=='O'){
                board[i][j-1]='1';
                q.push(make_pair(i,j-1));
            }
                
            if(i-1>=0 && board[i-1][j]=='O'){
                board[i-1][j]='1';
                q.push(make_pair(i-1,j));
            }
            if(i+1<n  && board[i+1][j]=='O'){
                board[i+1][j]='1';
                q.push(make_pair(i+1,j));
            }
            if(j+1 <m && board[i][j+1]=='O'){
                board[i][j+1]='1';
                q.push(make_pair(i,j+1));
            }
                
        } 
    }
};