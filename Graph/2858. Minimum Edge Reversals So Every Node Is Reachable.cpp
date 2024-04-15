//edges 不会形成cycle, 像tree
class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        unordered_map<int,unordered_map<int,int>>graph;
        unordered_map<int,unordered_map<int,int>>dp;
        for(auto & edge: edges){
            graph[edge[0]][edge[1]] = 0;
            graph[edge[1]][edge[0]] = 1;
        }

        function<int(int, int)> dfs = [&](int parent, int cur){
            if(dp.count(parent) && dp[parent].count(cur)){
                return dp[parent][cur];
            }
            dp[parent][cur] = 0;
            for(auto nxt: graph[cur]){
                if(nxt.first == parent) continue;
                dp[parent][cur] += dfs(cur, nxt.first) +  nxt.second;
            }
            return dp[parent][cur];
        };

        vector<int>res;
        for(int i = 0; i < n; ++i){
            res.push_back(dfs(-1, i));
        }
        return res;
    }
};



//edges 不会形成cycle, 像tree
class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_map<int, int>> G;
        for (auto& e : edges) {
            G[e[0]][e[1]] = 0, G[e[1]][e[0]] = 1;
        }
        vector<int> res(n, -1);

        function<int(int, int)> dp = [&](int i, int j) {
            int cur = 0;
            for (auto& k : G[j]) {
                if (k.first == i) continue;
                cur += dp(j, k.first) + k.second;
            }
            return cur;
        };

        function<void(int, int)> dfs = [&](int i, int v) {
            res[i] = v;
            for (auto& j : G[i])
                if (res[j.first] < 0)
                    dfs(j.first, v - j.second + G[j.first][i]);
        };

        dfs(0, dp(-1, 0));
        return res;
    }
};