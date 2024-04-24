class Solution {
public:
    void dfs(int cur, vector<int>&visited, unordered_map<int,unordered_set<int>>&graph){
        visited[cur] = 1;
        for(auto &nxt: graph[cur]){
            if(visited[nxt]) continue;
            dfs(nxt, visited, graph);
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        unordered_map<int,unordered_set<int>>graph;
        for(int i = 0; i < rooms.size(); ++i){
            for(auto& key: rooms[i]){
                graph[i].insert(key);
            } 
        }
        int n = rooms.size();
        vector<int>visited(n);
        dfs(0, visited, graph);
        return *min_element(visited.begin(), visited.end()) == 1;
    }
};



class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        stack<int> dfs; dfs.push(0);
        unordered_set<int> seen = {0};
        while (!dfs.empty()) {
            int i = dfs.top(); dfs.pop();
            for (int j : rooms[i])
                if (seen.count(j) == 0) {
                    dfs.push(j);
                    seen.insert(j);
                    if (rooms.size() == seen.size()) return true;
                }
        }
        return rooms.size() == seen.size();
    }
};