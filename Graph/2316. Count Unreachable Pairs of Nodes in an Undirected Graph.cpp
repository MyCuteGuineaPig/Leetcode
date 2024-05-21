class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<int>par(n);
        vector<int>rank(n);
        iota(par.begin(), par.end(), 0);
        function<int(int)> find = [&](int i){
            return par[i] == i ? i: par[i] = find(par[i]);
        };

        for(auto &edge: edges){
            int p0 = find(edge[0]), p1 = find(edge[1]);
            if(rank[p0] >= rank[p1]){
                par[p1] = p0;
                ++rank[p1];
            } else {
                par[p0] = p1;
            }
        }
        unordered_map<int, int>mp;
        for(int i = 0; i < n; ++i){
            ++mp[find(i)];
        }
        long long res = 0;
        for(auto &it: mp){
            long long cur_cnt = it.second; 
            long long remaining_cnt = n - it.second;
            res += cur_cnt * remaining_cnt;
        }
        return res/2;
    }
};


class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<int>visited(n);
        unordered_map<int, unordered_set<int>>graph;
        function<long long(int)> dfs = [&](int cur){
            long long cnt = 1;
            visited[cur] = 1;
            for(auto & nxt: graph[cur]){
                if(visited[nxt]) continue;
                cnt += dfs(nxt);
            }
            return cnt;
        };

        for(auto &edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        long long remaining = n;
        long long res = 0;
        for(int i = 0; i < n; ++i){
            if(visited[i]) continue;
            int cnt = dfs(i);
            res += cnt * (remaining - cnt);
            remaining -= cnt;
        }
        return res;
    }
};