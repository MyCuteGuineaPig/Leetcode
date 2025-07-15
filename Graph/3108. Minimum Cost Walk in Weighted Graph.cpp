class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int>parent(n);
        iota(parent.begin(), parent.end(), 0);
        vector<int>cost(n,-1);
        //or vector<int>cost(n, (1<<20)-1);
        function<int(int)> find = [&](int i) -> int {
            return parent[i] == i ? i: parent[i] = find(parent[i]);
        };
        for(auto & e: edges){
            cout<<e[0]<<" e[1] "<<e[1]<<endl;
            int p1 = find(e[0]), p2=find(e[1]);
            if (p1 != p2){
                cost[p1] &= cost[p2];
                parent[p2] = p1;
            }
            cost[p1] &= e[2];
        }
        vector<int>res;
        for(auto q: query){
            if(q[0] == q[1]){
                res.push_back(0);
            } else{
                int p1 = find(q[0]);
                int p2 = find(q[1]);
                if (p1 != p2) res.push_back(-1);
                else res.push_back(cost[p1]);
            }
        }
        return res;
    }
};


//DFS
class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        unordered_map<int, unordered_map<int, int>>graph;
        vector<int>cost(n, (1<<20)-1);
        vector<int>visited(n, -1);
    
        for(auto & e: edges){
            if(graph.count(e[0]) && graph[e[0]].count(e[1])) {
                graph[e[0]][e[1]] &= e[2]; 
                graph[e[1]][e[0]] &= e[2]; 
            } else {
                graph[e[0]][e[1]] = e[2]; 
                graph[e[1]][e[0]] = e[2]; 
            }
        }

        auto dfs = [&](this auto&& dfs, int cur, int root_id)->int{
            visited[cur] = root_id;
            int cur_cost =  (1<<20)-1;
            for(auto& [nxt, value]: graph[cur]){
                cur_cost &= value;
                if (visited[nxt] >= 0) continue;
                cur_cost &= dfs(nxt, root_id);
            }
            return cost[cur] = cur_cost;
        };
        for(int i = 0; i <n; ++i){
            if(visited[i] == -1)
                dfs(i, i);
        }
        vector<int>res;
        for(auto &q: query){
            int r_1 = visited[q[0]], r_2 = visited[q[1]];
            if(r_1 == r_2 ){
                res.push_back(cost[r_1]);
            }
            else {
                res.push_back(-1);
            }
        }
        return res;
    }
};

//DSF
class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        unordered_map<int, unordered_map<int, int>>graph;
        vector<int>cost(n, (1<<20)-1);
        vector<int>root(n, -1);
    
        for(auto & e: edges){
            if(graph.count(e[0]) && graph[e[0]].count(e[1])) {
                graph[e[0]][e[1]] &= e[2]; 
                graph[e[1]][e[0]] &= e[2]; 
            } else {
                graph[e[0]][e[1]] = e[2]; 
                graph[e[1]][e[0]] = e[2]; 
            }
        }

        auto dfs = [&](this auto&& dfs, int cur, int root_id)->int{
            if (root[cur] != -1)
                return  ((1<<20)-1); 
            root[cur] = root_id;
            int cur_cost =  (1<<20)-1;
            for(auto& [nxt, value]: graph[cur]){
                cur_cost &= value;
                //if (root[nxt] >= 0) continue;
                cur_cost &= dfs(nxt, root_id);
            }
            return cost[cur] = cur_cost;
        };
        for(int i = 0; i <n; ++i){
            if(root[i] == -1)
                dfs(i, i);
        }
        vector<int>res;
        for(auto &q: query){
            int r_1 = root[q[0]], r_2 = root[q[1]];
            if(r_1 == r_2 ){
                res.push_back(cost[r_1]);
            }
            else {
                res.push_back(-1);
            }
        }
        return res;
    }
};



//BFS
class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        unordered_map<int, unordered_map<int, int>>graph;
        vector<int>cost(n, (1<<20)-1);
        vector<int>root(n, -1);
    
        for(auto & e: edges){
            if(graph.count(e[0]) && graph[e[0]].count(e[1])) {
                graph[e[0]][e[1]] &= e[2]; 
                graph[e[1]][e[0]] &= e[2]; 
            } else {
                graph[e[0]][e[1]] = e[2]; 
                graph[e[1]][e[0]] = e[2]; 
            }
        }

        auto bfs = [&](this auto&& dfs, int cur){
            queue<int>q; 
            q.push(cur);
            int root_id = cur;
            root[cur] = root_id;
            int cur_cost = (1<<20) - 1; 

            while(!q.empty()){
                int top = q.front(); q.pop();
                for(auto& [nxt, value]: graph[top]){
                    cur_cost &= value;
                    if(root[nxt] != -1) continue;
                    root[nxt] = root_id;
                    q.push(nxt);
                }
            }
            cost[cur] = cur_cost;
        };
        for(int i = 0; i <n; ++i){
            if(root[i] == -1)
                bfs(i);
        }
        vector<int>res;
        for(auto &q: query){
            int r_1 = root[q[0]], r_2 = root[q[1]];
            if(r_1 == r_2 ){
                res.push_back(cost[r_1]);
            }
            else {
                res.push_back(-1);
            }
        }
        return res;
    }
};