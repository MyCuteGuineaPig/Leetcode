class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        for(auto e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }

        vector<int>visited(n);
        function<void(int)> dfs = [&](int cur){
            visited[cur] = 1;
            for(auto nxt: graph[cur]){
                if (visited[nxt] == 0)
                    dfs(nxt);
            }
        };
        int res = 0;
        for(int i = 0; i<n; ++i){
            if(visited[i] == 0){
                ++res;
                dfs(i);
            }
        }
        return res;
    }
};


class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int>p(n);
        iota(p.begin(), p.end(), 0);
        function <int(int)> find = [&](int v){
            return p[v] == v ? v: p[v] = find(p[v]);
        };
        for(auto & e: edges){
            int p0 = find(e[0]), p1 = find(e[1]);
            p[p1] = p0;
            n -= (p0 != p1);
        }
        return n;
    }
};