class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int>indegree(n);
        unordered_map<int,unordered_set<int>>graph;
        unordered_map<int, unordered_map<char,int>> mp;
        for(auto e: edges){
            ++indegree[e[1]];
            if (e[0] == e[1]) return -1;
            graph[e[0]].insert(e[1]);
        }

        queue<int>q; 

        for(int i = 0 ; i < n; ++i){
            if(indegree[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            mp[cur][colors[cur]] += 1;
            for(auto& nxt: graph[cur]){
                for(auto [color, count]: mp[cur]){
                    mp[nxt][color] = max(mp[nxt][color], count);
                }
                if (--indegree[nxt] == 0){
                    q.push(nxt);
                }
            }
        }
        if (mp.size() != n) {
            return -1;
        }
        int res = 0;
        for(auto & [point, m]: mp ){
            for(auto & [color, count]: m){
                res = max(res, count);
            }
        }
        return res;
    }
};