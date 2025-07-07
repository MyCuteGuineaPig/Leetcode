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


class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n -1)
            return false;
        vector<int>visited(n, 0);
        unordered_map<int, unordered_set<int>> mp;
        auto dfs = [&](this auto&& dfs, int cur) -> void {
            visited[cur] = 1;
            for(auto &nxt: mp[cur]){
                if(visited[nxt]) continue;
                dfs(nxt);
            }
        };
        for(const auto& e: edges){
            mp[e[0]].insert(e[1]);
            mp[e[1]].insert(e[0]);
        }
        dfs(0);
        return accumulate(visited.begin(), visited.end(), 0) == n;
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


//union find, all root must be 0, otherwise, some nodes are not connected to node 0 
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n -1)
            return false;
        vector<int>root(n, n); iota(root.begin(), root.end(), 0);
        auto find = [&](this auto& find, int i) -> int{
            return root[i] == i ? i : root[i] = find(root[i]);
        };
        for(const auto& e: edges){
            int r_0 = find(e[0]);
            int r_1 = find(e[1]);
            if (r_0 != r_1){
                if (r_0 > r_1) { 
                    swap(r_0, r_1);
                }
                root[r_1] = r_0;
            }
        }
        for(int i = 0 ; i < n; ++i) {
            int r = find(i);
            //cout<< " i " << i << " root "<<r<<endl;
        }
        return accumulate(root.begin(), root.end(), 0) == 0;
    }
};