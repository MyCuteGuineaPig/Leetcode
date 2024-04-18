/*

如果每个都在cycle中， 每个node的outgoing size = 总共的node - 1
*/

class Solution {
public:
    void dfs(unordered_map<int,unordered_set<int>>&graph, int cur, unordered_set<int>&visited){
        if(visited.insert(cur).second){
            for(auto &nxt: graph[cur])
                dfs(graph, nxt, visited);
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int,unordered_set<int>>graph;
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        unordered_set<int>visited;
        int res = 0;
        for(int i = 0; i<n; ++i ){
            if(visited.count(i) == 0){
                unordered_set<int>tmp_visited;
                dfs(graph, i, tmp_visited);
                res += all_of(tmp_visited.begin(), tmp_visited.end(), [&](int j){return graph[j].size() == tmp_visited.size()-1;});
                visited.insert(tmp_visited.begin(), tmp_visited.end());
            }
        }
        return res;
    }
};


class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int,unordered_set<int>>graph;
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        vector<int>visited(n);
        int res = 0;
        for(int i = 0 ; i < n; ++i){
            if (visited[i]) continue;
            visited[i] = 1;
            unordered_set<int>tmp;
            queue<int>q; q.push(i);
            while(!q.empty()){
                int top = q.front(); q.pop();
                tmp.insert(top);
                for (auto & nxt: graph[top]){
                    if(visited[nxt]) continue;
                    q.push(nxt);
                    visited[nxt] = 1;
                }
            }
            res += all_of(tmp.begin(), tmp.end(), [&](int j){return graph[j].size() == tmp.size()-1;});
        }
        return res;
    }
};