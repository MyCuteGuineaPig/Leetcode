/*
773. Sliding Puzzle

Time	                Space	                Difficulty
O((m * n) * (m * n)!)	O((m * n) * (m * n)!)	Hard	

On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Examples:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14
Note:

board will be a 2 x 3 array as described above.
board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].

*/

//BFS
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_map<int,vector<int>>moves = {{0,{1,3}},{1,{0,2,4}},{2,{1,5}},{3,{0,4}},{4,{3,1,5}},{5,{2,4}}};
        string s = to_string(board[0][0])+to_string(board[0][1])+to_string(board[0][2])
        +to_string(board[1][0])+to_string(board[1][1])+to_string(board[1][2]);

        unordered_map<string, int>map; //store the string and corresponding move
        map[s] = 0;
        queue<pair<string,int>>q({{s,s.find('0')}});
        while(q.size() && q.front().first!="123450"){
            int oldzero = q.front().second;   
            for(auto move: moves[oldzero]){
                string cur = q.front().first;
                swap(cur[move],cur[oldzero]);
                if(map.insert({cur,map[q.front().first]+1}).second)
                    q.push({cur,move});
            }
            q.pop();
        }
        return q.size() == 0? -1 : map["123450"];
    }
};

//DFS
class Solution {
public:
    unordered_map<int,vector<int>>moves = {{0,{1,3}},{1,{0,2,4}},{2,{1,5}},{3,{0,4}},{4,{3,1,5}},{5,{2,4}}};  

    int slidingPuzzle(vector<vector<int>>& board, int min_moves = INT_MAX) {
        string s = to_string(board[0][0])+to_string(board[0][1])+to_string(board[0][2])
        +to_string(board[1][0])+to_string(board[1][1])+to_string(board[1][2]);

        dfs(s, unordered_map<string, int>() = {}, s.find('0'), s.find('0'), 0, min_moves);
        return min_moves == INT_MAX ? -1 : min_moves;
    }

    void dfs(string s, unordered_map<string, int>&m, int cur_zero, int swap_zero, int cur_move, int &min_moves){
        swap(s[cur_zero],s[swap_zero]);
        if(s=="123450") min_moves = min(min_moves, cur_move);
        if(cur_move < min_moves &&(m[s] == 0 || m[s] > cur_move )){
            m[s] = cur_move;
            for(auto new_zero: moves[swap_zero])
                dfs(s,m, swap_zero, new_zero, cur_move+1, min_moves);
        }

    }
};