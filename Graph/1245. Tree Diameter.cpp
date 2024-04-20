//找最远的node, 
class Solution {
public:
    pair<int,int> bfs( unordered_map<int, unordered_set<int>>&graph,int cur){
        unordered_set<int>visited; visited.insert(cur);
        queue<int>q; q.push(cur);
        int distance = 0;
        int last_node = cur;
        while(!q.empty()){
            int size = q.size();
            for(int a = 0; a < size; ++a){
                int top = q.front(); q.pop();
                //cout<<" top "<<top<<" distnace "<<distance<<endl;
                for(auto &nxt: graph[top]){
                    if(visited.count(nxt)) continue;
                    visited.insert(nxt);
                    last_node = nxt;
                    q.push(nxt);
                }
            }
            if (!q.empty())
                ++distance;
        }
        return {last_node, distance};
    }

    int treeDiameter(vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        unordered_set<int>visited;
        for(auto & e: edges)
        {
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        auto [farthest_node, d1] = bfs(graph, 0);
        cout<<" farthest_node "<<farthest_node << " d1 "<<d1<<endl;
        auto [ x , distance] = bfs(graph, farthest_node);
        return distance;
    }
};



//https://leetcode.com/problems/tree-diameter/editorial/
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        int n  =edges.size()+1;
        vector<int>indegree(n);
        for(auto & e: edges)
        {
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
            indegree[e[0]]++;
            indegree[e[1]]++;
        }
        queue<int>q;
        for(int i = 0; i<n; ++i)
            if(indegree[i] == 1)
                q.push(i);
            
        int distance = 0;
        while(n > 2){
            n -= q.size();
            int size = q.size();
            for(int a = 0; a < size; ++a){
                int top = q.front(); q.pop();
                for(auto & nxt: graph[top]){
                    if(--indegree[nxt] == 1){
                        q.push(nxt);
                    }
                }
            }
            ++distance;
        }
        return 2*distance + (n == 2);
    }
};



class Solution {
public:

    int dfs(unordered_map<int, unordered_set<int>>&graph, unordered_set<int>&visited, int cur, int & res){
        int d1 = 0, d2 = 0;
        visited.insert(cur);
        for(auto & nxt: graph[cur]){
            if(visited.count(nxt)) continue;
            int tmp = dfs(graph, visited, nxt, res) + 1;
            if(tmp > d1){
                d2 = d1;
                d1 = tmp;
            } else if (tmp > d2){
                d2 = tmp;
            }
        }
        res = max(res, d1 + d2);
        return d1;
    }

    int treeDiameter(vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>>graph;
        for(auto & e: edges)
        {
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        int res = 0;
        unordered_set<int>visited;
        dfs(graph, visited,0, res);
        return res;
    }
};



class Solution {
public:

    int dfs(vector<vector<int>>& al, vector<bool>& visited, int i, int& diameter) {
        visited[i] = true;
        auto max_depth = 0;
        for (auto j : al[i]) {
            if (!visited[j]) {
            auto depth = dfs(al, visited, j, diameter);
            diameter = max(diameter, depth + max_depth);
            max_depth = max(depth, max_depth);
            }
        }
        return i == 0 ? diameter : max_depth + 1;
    }
    int treeDiameter(vector<vector<int>>& edges) {
        int diameter = 0;
        vector<bool> visited(edges.size() + 1);
        vector<vector<int>> al(edges.size() + 1);
        for (auto& e : edges) {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }
        return dfs(al, visited, 0, diameter);
    }
};