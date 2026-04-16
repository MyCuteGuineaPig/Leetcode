class Solution {
public:
    int dfs(unordered_map<int,unordered_set<int>>&graph, int cur, int start, int count){
        //cout<<" int "<<cur<<" start "<<start<<"  count "<<count<<endl;
        if(count == 2){
            return graph[cur].count(start);
        }
        int res = 0;
        for(auto nxt: graph[cur]){
            if (nxt < cur) continue; //avoid double counting
            res += dfs(graph, nxt, start, count + 1);
        }
        return res;
    }

    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int,unordered_set<int>>graph;
        for(auto & e: corridors){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }

        int res = 0;
        for(int i = 1; i <= n; ++i){
            res += dfs(graph, i, i, 0);
        }
        return res;
    }
};


class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int, unordered_set<int>>graph;
        auto dfs = [&](this auto&& dfs, int start, int cur, int count) -> int {
            if(count == 2) 
                return graph[start].count(cur);
            
            int res = 0;
            for(auto nxt: graph[cur]){
                res += dfs(start, nxt, count+1);
            } 
            return res;
        };
        for(auto corridor: corridors){
            int start = min(corridor[0], corridor[1]);
            int end = max(corridor[0], corridor[1]);
            graph[start].insert(end);
        }

        int res = 0;
        for(int i = 1; i <=n; ++i ) {
            res += dfs(i, i, 0);
        }
        return res; 
    }
};


class Solution {
public:
    int dfs(unordered_map<int,unordered_set<int>>&graph, int cur, int start, int count){
        //cout<<" int "<<cur<<" start "<<start<<"  count "<<count<<endl;
        if(count == 2){
            return graph[start].count(cur);
        }
        int res = 0;
        for(auto nxt: graph[cur]){
            res += dfs(graph, nxt, start, count + 1);
        }
        return res;
    }

    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int,unordered_set<int>>graph; 
        for(auto & e: corridors){
            graph[min(e[0], e[1])].insert(max(e[0], e[1])); //avoid double counting
        }

        int res = 0;
        for(int i = 1; i <= n; ++i){
            res += dfs(graph, i, i, 0);
        }
        return res;
    }
};



class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        vector<vector<int>>graph(n+1, vector<int>(n+1)); 
        for(auto & e: corridors){
            graph[min(e[0], e[1])][max(e[0], e[1])] = 1; //avoid double counting
        }

        int res = 0;
        for(int i = 1; i <n; ++i){
            for(int j = i + 1; j < n; ++j){
                for(int k = j + 1; graph[i][j] && k<=n; ++k){
                    res += graph[j][k] && graph[i][k];
                }
            }
        }
    

        return res;
    }
};



class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        // 使用 bitset 存儲每個點的鄰接關係
        // 因為 n <= 1000, bitset<1001> 佔用空間很小
        vector<bitset<1001>> adj(n + 1);
        for (auto& edge : corridors) {
            adj[edge[0]].set(edge[1]);//set 第edge[1]位为1
            adj[edge[1]].set(edge[0]);//set 第edge[0]位为1
        }

        int count = 0;
        // 遍歷每一條邊 (u, v)
        for (auto& edge : corridors) {
            int u = edge[0];
            int v = edge[1];
            
            // 找出同時與 u 和 v 相連的點 w
            // 利用 bitset 的按位與 (AND) 運算
            bitset<1001> common = adj[u] & adj[v];
            
            // 這些點的數量就是包含這條邊的三角形數量
            count += common.count();
        }

        // 因為每個三角形 [u, v, w] 有三條邊，所以會被計算三次
        return count / 3;
    }
};