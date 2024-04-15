class Solution {
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        vector<int>degree(n,0);
        for(auto & edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
            ++degree[edge[0]]; 
            ++degree[edge[1]];
        }
        queue<int>q;
        for(int i = 0; i<n; ++i){
            if(degree[i] == 1) {
                q.push(i);
            }
        }
        while(!q.empty()){
            int top = q.front(); q.pop();
            for(auto nxt: graph[top]){
                if(--degree[nxt] == 1){
                    q.push(nxt);
                }
            }
        }
        vector<int>res(n, 2*n);
        for(int i = 0; i < n; ++i){
            if(degree[i]>1){
                q.push(i);
                res[i] = 0;
            }
        }
        while(!q.empty()){
            int top = q.front(); q.pop();
            for(auto nxt: graph[top]){
                if(res[nxt] > res[top] + 1){
                    res[nxt] = res[top] + 1;
                    q.push(nxt);
                }
            }
        }
        return res;
    }
};




class Solution {
public:
    int find_cycle(unordered_map<int,unordered_set<int>>&graph, int cur, int parent, vector<int>&visited, unordered_set<int>&cycle){
        if(visited[cur]){
            return cur;
        }
        visited[cur] = 1;
        for(auto &nxt: graph[cur]){
            if(nxt == parent) continue;
            int cycle_node = find_cycle(graph, nxt, cur, visited, cycle);
            if(cycle_node >= 0){
                cycle.insert(cur);
            }
            if(cycle_node >= 0){ 
                //比如 1-> 2 -> 3 -> 4 -> 1, 当4 ->1 返回1, 当 cur = 1 时候, cycle_node = 1是cycle 的起点
                return cur == cycle_node? -1: cycle_node;
            }
        }
        return -1;
    }

    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        unordered_map<int,unordered_set<int>>graph;
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        vector<int>visited(n);
        unordered_set<int>cycle;
        find_cycle(graph, 0, -1, visited, cycle);
        
        vector<int>res(n, 2*n);
        queue<int>q;
        for(auto &c: cycle){
            q.push(c);
            res[c] = 0;
        }

        while(!q.empty()){
            int top = q.front(); q.pop();
            for( auto & nxt: graph[top]){
                if(res[nxt] > res[top] + 1){
                    res[nxt] = res[top] + 1;
                    q.push(nxt);
                }
            }
        }
        return res;
    }
};