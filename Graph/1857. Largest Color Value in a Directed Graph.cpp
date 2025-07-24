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


//
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
        int res = 0;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            mp[cur][colors[cur]] += 1;
            res = max(res, mp[cur][colors[cur]]);
            for(auto& nxt: graph[cur]){
                for(auto [color, count]: mp[cur]){
                    mp[nxt][color] = max(mp[nxt][color], count);
                }
                if (--indegree[nxt] == 0){
                    q.push(nxt);
                }
            }
        }
        return mp.size() != n? -1 : res;
    }
};




class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int m = colors.length();
        int ans = 0;
        vector<vector<int>> adj(m);
        // Kahn's algorithm
        vector<int> indegree(m);
        queue<int> q;
        int cnt = 0;
        // save maximum frequency of a path when passing specific node
        vector<array<int,26>> nodeColor(m);
        for (vector<int> const & e: edges) {
            int u = e[0], v = e[1];
            if (u == v) return -1; // self-loop return -1 immediately
            adj[u].push_back(v);
            indegree[v]++;
        }
        // Start with the zero indegree
        for (int i = 0; i < m; i++) {
            if (!indegree[i]) q.push(i);
        }
        
        while (q.size()) {
            int u = q.front();
            q.pop();
            cnt++; // count visited nodes
            ans = max(ans, ++nodeColor[u][colors[u] - 'a']);
            for (int const & v: adj[u]) {
                indegree[v]--;
                // update maximum frequency of color at node 'v'
                for (int i = 0; i < 26; i++) nodeColor[v][i] = max(nodeColor[v][i], nodeColor[u][i]);
                if (!indegree[v]) {
                    q.push(v);
                }
            }
        }

        return (cnt == m)? ans: -1;
    }
};


//DFS
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        unordered_map<int,unordered_set<int>>graph;
        vector<array<int,26>> nodeColor(n);
        for(auto e: edges){
            if (e[0] == e[1]) return -1;
            graph[e[0]].insert(e[1]);
        }

        vector<int>visited(n);
        int res = 0;
        auto dfs = [&](this auto&& dfs, int cur, vector<int>&onstack) -> bool{
            visited[cur] = onstack[cur] = 1;
            for(auto nxt: graph[cur]){
                if(!visited[nxt]) {
                    if (dfs(nxt, onstack)) return true;
                    //cout<<"cur "<<cur<<" nxt "<<nxt<<endl;

                } else if (onstack[nxt]){
                    return true;
                }
                //不能在if block里，否则去过的点，不能被使用
                /*
                比如 
                    1 - -------->   5 ---------> 6 
                    1 -->3 -->4 --> 5 ---------> 6 
                    在点4 看不到5 的value
                
                */
                for(int i = 0; i<26; ++i)
                    nodeColor[cur][i] = max(nodeColor[cur][i], nodeColor[nxt][i]);
            }
            onstack[cur] = 0;
            nodeColor[cur][colors[cur] - 'a'] += 1;            
            res = max(res,  nodeColor[cur][colors[cur] - 'a']);
            
            return false;
        };

        for(int i = 0; i<n; ++i){
            if(!visited[i]) {
                vector<int>onstack(n);
                if(dfs(i, onstack)) return -1;
            }
        }
        
        return res;
    }
};


//DFS

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        unordered_map<int,unordered_set<int>>graph;
        vector<array<int,26>> nodeColor(n);
        for(auto e: edges){
            if (e[0] == e[1]) return -1;
            graph[e[0]].insert(e[1]);
        }

        vector<int>visited(n);
        int res = 0;
        auto dfs = [&](this auto&& dfs, int cur, vector<int>&onstack) -> bool{
            if (onstack[cur])
                return true;
            if(visited[cur])
                return false;
            visited[cur] = onstack[cur] = 1;
            for(auto nxt: graph[cur]){
                if (dfs(nxt, onstack)) return true;
                
                for(int i = 0; i<26; ++i)
                    nodeColor[cur][i] = max(nodeColor[cur][i], nodeColor[nxt][i]);
            }
            onstack[cur] = 0;
            nodeColor[cur][colors[cur] - 'a'] += 1;
            
            res = max(res,  nodeColor[cur][colors[cur] - 'a']);
            
            return false;
        };

        for(int i = 0; i<n; ++i){
            if(!visited[i]) {
                vector<int>onstack(n);
                if(dfs(i, onstack)) return -1;
            }
        }
        
        return res;
    }
};