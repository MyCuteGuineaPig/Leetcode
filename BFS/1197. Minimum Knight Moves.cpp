//BFS
class Solution {
public:
    vector<pair<int,int>> dir = {{-2,1},{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}};
    int minKnightMoves(int x, int y) {
        if(x == 0 && y == 0)
            return 0;
        queue<pair<int,int>>q; q.push({0,0});
        set<pair<int,int>>st; st.insert({0,0});
        int cnt = 0;
        x = abs(x);
        y = abs(y);
        while (!q.empty()) {
            int size = q.size(); 
            ++cnt;
            for(int a = 0; a < size; ++a){
                auto top = q.front(); q.pop();
                for(auto& [i, j]: dir){
                    int xx = top.first + i; 
                    int yy = top.second + j;
                    if (xx < -2 || xx > x+2 || y <-2 || yy >y+2 || abs(xx) + abs(yy) > 300 )   continue;
                    if(st.count({xx, yy})) continue;
                    if (x == xx && y == yy) {
                        return cnt;
                    }
                    st.insert({xx,yy});
                    q.push({xx,yy});
                }
            }
        }
        return -1;
    }
};

//DP
class Solution {
public:
    int visited[310][310];
    int solve(int x, int y){
        if(x==0 && y==0)
            return 0;
        if(abs(x)+abs(y) == 2)
            return 2;
        if(x<0 || y<0)
            return solve(abs(x), abs(y));
        if(visited[x][y]>0)
            return visited[x][y];
        int result = 1 + min(solve(x-2, y-1), solve(x-1, y-2));
        visited[x][y] = result;
        return result;
    }
    int minKnightMoves(int x, int y) {
        for(int i=0; i<310; i++){
            for(int j=0; j<310; j++){
                visited[i][j] = 0;
            }
        }
        return solve(x, y);
    }
};


class Solution {
public:
    int dfs(int x, int y, vector<vector<int>>&dp){
        //cout<<" i "<<x<<" y "<<y<<endl;
        if(x<0 || y<0){
            return dfs(abs(x), abs(y), dp);
        }
        if (abs(x) + abs(y) == 2) { //必须需要他，
        //比如(1,1) 最佳方式是 1,1 ->  -1, 2 (-2, + 1) 有加法的 -> 0, 0 (+1, -2)
            return 2;
        } 
        if(x == 0 && y == 0){
            return 0;
        }
        if (dp[x][y]) {
            return dp[x][y];
        }
        dp[x][y] = 1 + min(dfs(x-2, y-1, dp), dfs(x-1, y-2, dp));
        return dp[x][y];
    }

    int minKnightMoves(int x, int y) {
        vector<vector<int>>dp(310, vector<int>(310));
        return dfs(x, y, dp);
    }
};


