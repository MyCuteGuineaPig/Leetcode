
/*
52. N-Queens II

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.





*/


class Solution {
public:
    int totalNQueens(int n)  {
        int ans = 0;
        vector<string> board(n, string(n, '.'));
        vector<int>visited(5*n-2, 1);
        helper(ans,board,visited,0,n);
        return ans;
    }
    
    void helper(int& ans, vector<string>& board,vector<int>& visited, int row, int n){
        if(row==n){
            ans++;
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