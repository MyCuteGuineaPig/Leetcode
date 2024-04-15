class Solution {
public:
    bool dfs(unordered_map<int, unordered_set<int>>&graph, vector<int>&visited, int cur, int parent){
        //cout<<" in "<<cur<<endl;
        visited[cur] = 1;
        for(auto nxt: graph[cur]){
            if(nxt == parent) continue;
            if (visited[nxt]) return false;
            if (!dfs(graph, visited, nxt, cur)){
                return false;
            }
        }
        return true;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        vector<int>visited(n);
        bool res = dfs(graph, visited, 0, -1);
        return res ? accumulate(visited.begin(), visited.end(), 0) == n : false;
    }
};


//edges size 必须是 n-1 才能没有cycle
class Solution {
public:
    void dfs(unordered_map<int, unordered_set<int>>&graph, vector<int>&visited, int cur, int parent){
        //cout<<" in "<<cur<<endl;
        visited[cur] = 1;
        for(auto nxt: graph[cur]){
            if (visited[nxt]) continue;
            dfs(graph, visited, nxt, cur);
        }
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n-1 )
            return false;
        unordered_map<int, unordered_set<int>>graph;
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        vector<int>visited(n);
        dfs(graph, visited, 0, -1);
        return accumulate(visited.begin(), visited.end(), 0) == n;
    }
};