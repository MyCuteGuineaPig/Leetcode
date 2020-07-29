/**
 Method 1 : BFS

  3 - 5，  更新的是 visited[5] = path | 1 << 5  
  5 - 3    更新的是 visited[3] = path (因为已经去过3了，但path 多了个5), 之后path 不会再经过5
 */
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        if(graph.size()==1) 
            return 0;
        queue<pair<int,int>>q; 
        unordered_map<int,unordered_set<int>>visited;//没有这个TLE
            
        for(int i = 0; i<graph.size();++i){
            q.push({i,1<<i});
            visited[i].insert(1<<i);
        }
            
        int step = 0, target = (1 << graph.size())-1;
        
        while(!q.empty()){
            ++step;
            for(int z = q.size(); z>0; --z){
                
                pair<int,int>top = q.front(); q.pop();
                for(auto nxt: graph[top.first]){
                    
                    int path = top.second | (1<<nxt);
                    if(visited[nxt].count(path) )
                        continue;
                    visited[nxt].insert(path);
                    if(path == target){
                        return step;
                    }

                    q.push({nxt,path});
                }
            }
        }
        return -1;
    }
};


/**
 *Method 2 DP

dp[i][path] 表示现在i点（Destination），走过路径最短为path的最短路径

dp[0][3(00000...00011)] = 2 means the distance starting point 0 through 0, 1 is 2
dp[1][7(00000...00111)] = 3 means the distance starting point 1 through 0, 1, 2 is 3.
 */

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        if(graph.size()==1) 
            return 0;
        int n = graph.size();
        vector<vector<int>>dp(n, vector<int>(1<<n, numeric_limits<int>::max()));
        
        queue<pair<int,int>>q; 
        for(int i = 0; i<graph.size();++i){
            q.push({i,1<<i});
            dp[i][1<<i] = 0;
        }
          
        while(!q.empty()){
            for(int z = q.size(); z>0; --z){
                
                pair<int,int>top = q.front(); q.pop();
                for(auto nxt: graph[top.first]){
                    
                    int path = top.second | (1<<nxt);
                    if(dp[nxt][path] > dp[top.first][top.second]+1){
                        dp[nxt][path] = dp[top.first][top.second]+1;
                        q.push({nxt,path});
                    }
                   
                }
            }
        }
        int res =  numeric_limits<int>::max();
        for(int i = 0; i < n; ++i)
            res = min(res, dp[i][(1<<n)-1]);
        return res;
    }
};

/*
DFS
In each dfs function call, visit all the nodes which has the least visit times. 

visited[n] == minv

比如   1 可以到3,  3 可以到 1, 4 ;   4 可以到 2;   1 <-> 3 可以循环

      进入1,  minv = visited[3] = 0
            进入3, minv = visited[4] = 0， 而不选择进入1，

 */
class Solution {
public:
    int result;
    void dfs(vector<vector<int>>& graph, vector<int>& cur, vector<int>& visited, int count) {
        if (result == graph.size()) return;
        if (count == graph.size()) {
            result = min(result, int(cur.size()));
            return;
        }
        if (cur.size() >= result) return;
        int pos = cur.back();
        
        int minv = INT_MAX;
        for (auto n : graph[pos]) minv = min(minv, visited[n]);
        for (auto n : graph[pos]) {
            if (visited[n] == minv) {
                cur.push_back(n);
                if (!visited[n]) count++;
                visited[n]++;
                dfs(graph, cur, visited, count);
                visited[n]--;
                if (!visited[n]) count--;
                cur.pop_back();                
            }
        }
    }
    
    int shortestPathLength(vector<vector<int>>& graph) {
        result = INT_MAX;
        vector<int> cur;
        vector<int> visited(graph.size(), 0);
        int count = 0;
        for (int i = 0; i < graph.size(); i++) {
            cur.push_back(i);
            visited[i]++;
            count++;
            dfs(graph, cur, visited, count);
            count--;
            visited[i]--;
            cur.pop_back();
        }
        return result - 1;
    }
};


/**
 DP:
 
 dis[x][y] represents the minimun distance between node x and node y
 .
 dp[group][dst] represents the shortest distance that a man could walk through all nodes in the "group", 
    and finally finished at the node "dst" ("dst" is one of the node in "group").

"group". For example, If group only has node 0 and node 2, the value of group is 101 in binary


Pick a node that is in the "group"(for example, node u), and pick a node that is not in the "group"(for example, node v). 
Then update dp[group+v][v] by getting the minimum value between dp[group+v][v] and dp[group][u] + dis[u][v].
 */
class Solution {
public:
    
    int dis[15][15];
    int dp[1<<13][13];
    
    void floyd(int n) {
        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]); //update distance 
    }
    int DP(int n) {
        memset(dp, 0x3f, sizeof(dp));
        for (int i=0; i<n; i++) //初始化path
            dp[1<<i][i] = 0;
        for (int group=1; group<(1<<n); group++)//看每一个path
            for (int u=0; u<n; u++)
                for (int v=0; v<n; v++) {
                    int src = 1 << u, dst = 1 << v; //比如 u = 3, v =5, 从3出发，到达5
                    if ((group & src) && !(group & dst)) // !(group & dst) 表示group 并没有到 v点
                    // (group & src): group 到达过u点
                        dp[group|dst][v] = min(dp[group][u] + dis[u][v], dp[group|dst][v]);
                        //dp[group][u]:  表示 path 为group, 最后到达点是u, 需要最短距离,  + dis[u][v]的 u 到 v的最短距离
                }
        int min_dis = numeric_limits<int>::max();
        for (int i=0; i<n; i++)
            min_dis = min(dp[(1<<n)-1][i], min_dis);
        return min_dis;
    }
    
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        memset(dis, 0x3f, sizeof(dis));
        for (int i=0; i<n; i++) {
            int to_size = graph[i].size();
            for (int j=0; j<to_size; j++) {
                int u = i, v = graph[i][j];
                dis[u][v] = 1;
            }
        }
        floyd(n);
        int min_dis = DP(n);
        return min_dis;
    }
};

/**
 * 
 Method 5:

int bitMask: mask of all the nodes we visited so far: 0 -> not visited, 1 -> visited (Originally this was Set<Integer>of
     all nodes we visited so far, but since the Solution TLE and N <= 12, it turns out we can use a bitMask 
     and 32 bits total in an Integer can cover all the possibilities. This is a small speed up optimization.)
int curr: current node we are on
int cost: the total cost in the path.

Each path taken will have a unique combination of these 3 variables.
 */


struct Tuple {
    int bitMask;
    int curr;
    int cost;

    Tuple(int bit, int n, int c) {
        bitMask = bit;
        curr = n;
        cost = c;
    }

    bool equals(const Tuple& p) const {
        return bitMask == p.bitMask && curr == p.curr && cost == p.cost;
    }

    int hashCode() const {
        return 1331 * bitMask + 7193 * curr + 727 * cost;
    }
};



struct Hash {
    size_t operator() (const Tuple &p) const {
        return p.hashCode();
    }
};

static bool operator==(const Tuple& lhs, const Tuple& rhs) {
    return lhs.equals(rhs);
}

class Solution {
public:
     int shortestPathLength(vector<vector<int>>& graph) {

        int N = graph.size();

        queue<Tuple> q;
        unordered_set<Tuple, Hash> visited;

        for (int i = 0; i < N; i++) {
            int tmp = (1 << i);
            visited.emplace(Tuple(tmp, i, 0));
            q.emplace(Tuple(tmp, i, 1));
        }

        while (!q.empty()) {
            Tuple curr = q.front();
            q.pop();

            if (curr.bitMask == (1 << N) - 1) {
                return curr.cost - 1;
            }
            else {
                auto& neighbors = graph[curr.curr];

                for (int v : neighbors) {
                    int bitMask = curr.bitMask;
                    bitMask |= (1 << v);

                    Tuple t(bitMask, v, 0);
                    if (!visited.count(t)) {
                        q.emplace(Tuple(bitMask, v, curr.cost + 1));
                        visited.emplace(t);
                    }
                }
            }
        }
        return -1;
    }
};