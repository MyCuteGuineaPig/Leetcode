class Solution {
public:
    void DFS(unordered_map<int,vector<int>>&path, int cur, int& res, unordered_set<int>&visited){
        ++res;
        visited.insert(cur);
        for(auto i: path[cur])
            if (visited.count(i) == 0)
                DFS(path, i, res, visited);
    }
    
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int>r(restricted.begin(),restricted.end());
        unordered_map<int,vector<int>>path;
        for(auto e: edges)
            if(r.count(e[0]) == 0 && r.count(e[1]) == 0){
                path[e[0]].push_back(e[1]);
                path[e[1]].push_back(e[0]);
            }
        int res = 0;
        unordered_set<int>visited;
        DFS(path, 0, res, visited);
        
        return res;
    }
};

class Solution {
public:
    int DFS(unordered_map<int,vector<int>>&path, int cur, unordered_set<int>&visited){
        int res = 1;
        visited.insert(cur);
        for(auto i: path[cur])
            if (visited.count(i) == 0)
                res += DFS(path, i, visited);
        return res;
    }
    
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int>r(restricted.begin(),restricted.end());
        unordered_map<int,vector<int>>path;
        for(auto e: edges)
            if(r.count(e[0]) == 0 && r.count(e[1]) == 0){
                path[e[0]].push_back(e[1]);
                path[e[1]].push_back(e[0]);
            }
        unordered_set<int>visited;
        return DFS(path, 0, visited);;
    }
};


//BFS
class Solution {
public:    
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int>r(restricted.begin(),restricted.end());
        unordered_map<int,vector<int>>path;
        for(auto e: edges)
            if(r.count(e[0]) == 0 && r.count(e[1]) == 0){
                path[e[0]].push_back(e[1]);
                path[e[1]].push_back(e[0]);
            }
        unordered_set<int>visited = {0};
        queue<int>q;
        q.push(0);
        int res = 1;
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i<size; ++i){
                int cur = q.front(); q.pop();
                for(auto nxt: path[cur]){
                    if(visited.count(nxt) == 0)
                    {
                        ++res;
                        visited.insert(nxt);
                        q.push(nxt);
                    }
                }
            }
        }
        return res;
    }
};


//BFS
class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>&e , vector<int>& r) {
        unordered_set<int> s(begin(r),end(r));
        vector<vector<int>> graph(n);
        for(auto i:e) graph[i[0]].push_back(i[1]) , graph[i[1]].push_back(i[0]);
        queue<int> q;
        vector<bool> seen(n);
        int cnt=0;
        q.push(0);
        seen[0]=true;
        while(q.size()){
            auto node= q.front(); q.pop();
            if(s.count(node)) continue;
            cnt++;
            for(auto j:graph[node]) //Put Neighbours
                if(!seen[j]) seen[j]=true , q.push(j);
        }
        return cnt;
    }
};