class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;
        unordered_map<int,unordered_set<int>>graph;
        for(auto &e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        queue<int>q; q.push(source);
        vector<int>visited(n); visited[source] = 1;
        while(!q.empty()){
            int size = q.size();
            for(int a = 0; a < size; ++a){
                int top = q.front(); q.pop();
                for(auto &nxt: graph[top]){
                    if(visited[nxt]) continue;
                    if (nxt == destination) return true;
                    visited[nxt] = 1;
                    q.push(nxt);
                }
            }
        }
        return false;
    }
};


class Solution {
public:
    bool dfs(unordered_map<int,unordered_set<int>>&graph,  vector<int>&visited, int cur, int destination){
        if (cur == destination)
            return true;
        visited[cur] = 1;
        for(auto & nxt:graph[cur]){
            if(visited[nxt]) continue;
            if (dfs(graph, visited, nxt, destination))
                return true;
        }
        return false;
    }

    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;
        unordered_map<int,unordered_set<int>>graph;
        for(auto &e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        vector<int>visited(n); visited[source] = 1;
        
        return dfs(graph, visited, source, destination);
    }
};


//Union Find
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;
        vector<int>parent(n); 
        iota(parent.begin(), parent.end(), 0);
        function <int(int)> find = [&](int i){
            return parent[i] == i ? i : parent[i] = find(parent[i]);
        };
        unordered_map<int,unordered_set<int>>graph;
        for(auto &e: edges){
            int p0 = find(e[0]);
            int p1 = find (e[1]);
            parent[p0] = p1;
        }
        return find(source) == find(destination);
    }
};