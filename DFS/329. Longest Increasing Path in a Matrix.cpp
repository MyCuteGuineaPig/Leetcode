/*
329. Longest Increasing Path in a Matrix.cpp

Time	    Space	    Difficulty
O(m * n)	O(m * n)	Hard

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.

*/

/**
 * 
 * some observations:
https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C++
The nodes which have odd degrees (int and out) are the entrance or exit. In your example it’s JFK and A.

If there are no nodes have odd degrees, we could follow any path without stuck until hit the last exit node

The reason we got stuck is because that we hit the exit

In your given example, nodes A is the exit node, we hit it and it’s the exit. So we put it to the result as the last node.
*/

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>>m; 
        vector<string>res;
        for(auto t: tickets){
            m[t.first].push(t.second);
        }
        dfs("JFK", res, m);
        reverse(res.begin(),res.end());
        return res;
    }

     void dfs(string cur, vector<string>& res, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& m)      {
        //cout<<"cur " << cur <<endl;
        while(!m[cur].empty()){
            string s = m[cur].top();
            m[cur].pop();
            //cout<<"before dsf cur "<<cur<<" size "<<m[cur].size()<<endl;
            dfs(s, res, m);
            //cout<<"after dfs "<<cur<<" size "<<m[cur].size()<<endl;
        }
        //cout<<"push back "<<cur<<endl;
        res.push_back(cur);
    }
};


//DFS with memoization
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int longest = 0;
        vector<vector<int>>visited(matrix.size(), vector<int>(matrix[0].size(), 0));
        for(int i = 0; i<matrix.size(); i++)
            for(int j = 0; j<matrix[i].size(); j++)
                longest = max(longest, helper(matrix, visited, i, j));

        return longest;
    }
    vector<pair<int,int>>dir = {{0,1},{1,0},{0,-1},{-1,0}};
    
    int helper(vector<vector<int>>& matrix, vector<vector<int>>&visited, int i, int j){
        if(visited[i][j]) return visited[i][j];
        int res  = 1;
        for(auto p: dir){
            int x = i + p.first, y = j + p.second;
            //cout<<"i "<<i<<" j "<<j<<" x "<<x<<" y " << y <<endl;
            if(x>=matrix.size() || x<0 || y>=matrix[0].size() || y<0 || matrix[x][y]<=matrix[i][j]) continue;
            res = max(res, 1+helper(matrix, visited, x, y));
        }
        return visited[i][j] = res;
    }
};


class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int longest = 0;
        vector<vector<int>>visited(matrix.size(), vector<int>(matrix[0].size(), 0));
        for(int i = 0; i<matrix.size(); i++)
            for(int j = 0; j<matrix[i].size(); j++){
                longest = max(longest, helper(matrix, visited, i, j));
                //cout<<"i "<<i<<" j "<<j<<" res "<<longest<<endl;
            }
        return longest;
    }

    int helper(vector<vector<int>>& matrix, vector<vector<int>>&visited, int i, int j){
        if(visited[i][j]) return visited[i][j];
        int down = 1, right = 1, left= 1, up = 1;
        if(i<matrix.size()-1 && matrix[i+1][j] > matrix[i][j] ) 
            down = 1 + helper(matrix, visited, i+1, j);
        if(j<matrix[0].size()-1 && matrix[i][j+1] > matrix[i][j])
            right = 1 +  helper(matrix, visited, i, j+1);
        if(i>0 && matrix[i-1][j] > matrix[i][j])
            up = 1 +  helper(matrix, visited, i-1, j);
        if(j>0 && matrix[i][j-1] > matrix[i][j])
            left = 1 +  helper(matrix, visited, i, j-1);
        return visited[i][j] = max(up, max(left, max(down, right)));
    }
};


class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (!rows) return 0;
        int cols = matrix[0].size();
        
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        std::function<int(int, int)> dfs = [&] (int x, int y) {
            if (dp[x][y]) return dp[x][y];
            vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
            for (auto &dir : dirs) {
                int xx = x + dir[0], yy = y + dir[1];
                if (xx < 0 || xx >= rows || yy < 0 || yy >= cols) continue;
                if (matrix[xx][yy] <= matrix[x][y]) continue;
                dp[x][y] = std::max(dp[x][y], dfs(xx, yy));
            }
            return ++dp[x][y];
        };
        
        int ret = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ret = std::max(ret, dfs(i, j));
            }
        }
        
        return ret;
    }
};


 //BFS: 一个一个移掉peak的点(peak点是：四周有任何一点比现在这个点大)，一共移动几次，就有几个最大值
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int longest = 0;
        vector<pair<int,int>>dir = {{0,1},{1,0},{0,-1},{-1,0}};
        int count = matrix.size() * matrix[0].size();
        while(count > 0){
            vector<pair<int,int>>remove;
            for(int i = 0; i<matrix.size(); i++){
                for(int j = 0; j<matrix[i].size(); j++){
                    if(matrix[i][j] == numeric_limits<int>::min()) continue;
                    bool isremove = true;
                    for(auto p: dir){
                        int x = i + p.first, y = j + p.second;
                        if(x>=matrix.size() || x<0 || y>=matrix[0].size() || y<0) continue;
                        if(matrix[x][y]>matrix[i][j]){
                            isremove = false;
                            break;
                        }
                    }
                    if(isremove)
                        remove.push_back({i,j});
                }
            }

            for(auto p: remove){
                matrix[p.first][p.second] = numeric_limits<int>::min();
                count--;
            }
            longest++;
        }
        return longest;
    }
    
};

