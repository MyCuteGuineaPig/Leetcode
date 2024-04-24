class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        auto cmp = [](const tuple<int, string,int,int>& a, const tuple<int, string,int,int>& b){
            if(get<0>(a) != get<0>(b)) {return get<0>(a) > get<0>(b);}
            return get<1>(a) > get<1>(b);
        };
        priority_queue<tuple<int, string,int,int>, vector<tuple<int,string, int,int>>, decltype(cmp)>pq(cmp);
        pq.push({0, "", ball[0], ball[1]});

        static vector<vector<int>>dirs = {{1, 0},{0,-1},{-1,0},  {0,1}};
        vector<string> ins = {  "d","l","u", "r"};

        int n = maze.size(), m = maze[0].size();
        vector<vector<pair<int, string>>>visited(n, vector<pair<int,string>>(m));
         visited[ball[0]][ball[1]] = {1, ""};

        function<int(int, int)> isValid = [&](int i, int j){
            return i < n && i >= 0 && j < m && j >=0 && maze[i][j] != 1;
        };

       
        while(!pq.empty()){
            int dist = get<0>(pq.top());
            string d = get<1>(pq.top());
            int x = get<2>(pq.top());
            int y = get<3>(pq.top());
            pq.pop();
            if(x == hole[0] && y == hole[1]){
                return d;
            }
            for(int i = 0; i < 4; ++i){
                int a = x;
                int b = y;
                int new_dis = dist;

                while(isValid(a + dirs[i][0], b + dirs[i][1])){
                    a += dirs[i][0];
                    b += dirs[i][1];
                    ++new_dis;
                    if (a == hole[0] && b == hole[1]){
                        break;
                    }
                }
                
                if (isValid(a, b) && (visited[a][b].first == 0 || visited[a][b].first == new_dis && d + ins[i] < visited[a][b].second)){
                    visited[a][b] = {new_dis, d+ins[i]};
                    pq.push({new_dis,d + ins[i], a, b});
                }
            }
        }
        return "impossible";
    }
};


class Solution {
public:
        string roll(vector<vector<int>>& maze, int rowBall, int colBall, const vector<int>& hole, 
        int d_row, int d_col, int steps, const string& path, pair<string, int>& res)
    {
        if (steps < res.second) {
            if (d_row != 0 || d_col != 0) { // both are zero for the initial ball position.
                while ((rowBall + d_row) >= 0 && (colBall + d_col) >= 0 && (rowBall + d_row) <  maze.size() 
                    && (colBall + d_col) < maze[0].size() && maze[rowBall + d_row][colBall + d_col] != 1) 
                {
                    rowBall += d_row;
                    colBall += d_col;
                    ++steps;
                    if (rowBall == hole[0] && colBall == hole[1] && steps < res.second) res = {path, steps};
                }
            }
            if (maze[rowBall][colBall] == 0 || steps + 2 < maze[rowBall][colBall]) {
                maze[rowBall][colBall] = steps + 2; // '1' is for the walls.
                if (d_row == 0) roll(maze, rowBall, colBall, hole, 1, 0, steps, path + "d", res);
                if (d_col == 0) roll(maze, rowBall, colBall, hole, 0, -1, steps, path + "l", res);
                if (d_col == 0) roll(maze, rowBall, colBall, hole, 0, 1, steps, path + "r", res);
                if (d_row == 0) roll(maze, rowBall, colBall, hole, -1, 0, steps, path + "u", res);
            }
        }
        return res.first;
    }
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) 
    {
        return roll(maze, ball[0], ball[1], hole, 0, 0, 0, "", pair<string, int>() = {"impossible", INT_MAX});
    }
    }
};