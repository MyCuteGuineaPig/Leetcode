//可以用 parent 代替visited
class Solution {
public:
    void dfs( unordered_map<int,unordered_map<int,int>>&graph, int parent, int cur, int& change){
        for(auto & nxt: graph[cur]){
            if(nxt.first == parent) continue;
            change += nxt.second;
            dfs(graph,  cur, nxt.first, change);
        }
    }

    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int,unordered_map<int,int>>graph;
        for(auto & connection: connections){
            graph[connection[0]][connection[1]] = 1;
            graph[connection[1]][connection[0]] = 0;
        }
        int change = 0;
        dfs(graph, -1, 0, change);
        return change;
    }
};


class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int,unordered_map<int,int>>graph;
        for(auto & connection: connections){
            graph[connection[0]][connection[1]] = 1;
            graph[connection[1]][connection[0]] = 0;
        }
        queue<pair<int,int>>q; q.push({-1, 0});
        int change = 0;
        while(!q.empty()){
            auto [parent, top] = q.front(); q.pop();
            for (auto &nxt: graph[top]){
                if(nxt.first != parent){
                    change += nxt.second;
                    q.push({top, nxt.first});
                }
            }
        }
        return change;
    }
};


class Solution {
public:
    int dfs(vector<vector<int>> &al, vector<bool> &visited, int from) {
        auto change = 0;
        visited[from] = true;
        for (auto to : al[from])
            if (!visited[abs(to)])
                change += dfs(al, visited, abs(to)) + (to > 0);
        return change;        
    }
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> al(n);
        for (auto &c : connections) {
            al[c[0]].push_back(c[1]);
            al[c[1]].push_back(-c[0]);
        }
        return dfs(al, vector<bool>(n) = {}, 0);
    }
};
