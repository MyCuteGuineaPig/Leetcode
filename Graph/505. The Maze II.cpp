class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        static vector<vector<int>>dirs = {{-1,0}, {0,-1}, {0, 1}, {1,0}};
        int n = maze.size(), m = maze[0].size();

        auto isValid = [&](int i, int j){
            return i >= 0 && j >= 0 && i < n && j < m && maze[i][j] != 1;
        };
        vector<vector<int>>dist(n, vector<int>(m, numeric_limits<int>::max()));
        dist[start[0]][start[1]] = 0;
        
        auto cmp = [&](const vector<int>& a, const vector<int>&b){
            return a[2] > b[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)>pq(cmp);
        pq.push({start[0], start[1], 0});
        while(!pq.empty()){
            int x = pq.top()[0],  y = pq.top()[1], cur_dist = pq.top()[2];
            //cout<<" x "<<x<<" y= "<<y<< " cur_dist= "<<cur_dist<<endl;
            pq.pop();
            if(x == destination[0] && y == destination[1]){
                return cur_dist;
            }
            for(auto &dir: dirs){
                int i = x;
                int j = y;
                int cnt = 0;
                while(isValid(i +  dir[0], j + dir[1])){
                    i += dir[0]; j += dir[1];
                    ++cnt;
                }
                if(isValid(i, j) && dist[i][j] > cnt + cur_dist){
                    dist[i][j] =cnt + cur_dist;
                    //cout<<" x "<<x<<" y= "<<y<< " cur_dist= "<<cur_dist
                    //    <<" i= "<<i<<" j= "<<j<< "  cnt + cur_dist= "<< cnt + cur_dist<<endl;
                    pq.push({i,j, cnt + cur_dist});
                }
            }
        }
        return -1;
    }
};