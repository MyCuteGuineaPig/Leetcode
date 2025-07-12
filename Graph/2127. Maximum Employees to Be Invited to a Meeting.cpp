/*

一个重要的assumption, 当与cycle 为2相连的点形成不了一个cycle

比如 
  1 <-> 2 
        ^
        |
        3 <- 5 <- 6 

1,2 形成cycle, 如果有3相连，一定不会再行程cycle， 
因为每个点 只能指向一个点!!! 所以3不能指向2的同时 指向5或者6
 */

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<int>in_degree(n, 0);
        vector<int>depth(n, 1);
        for(int i = 0; i < n; ++i){
            ++in_degree[favorite[i]];
        }
        
        queue<int> q_indegree_0;
        //find all nodes without indegree
        for(int i = 0 ; i<n; ++i){
            if(in_degree[i] == 0)
                q_indegree_0.push(i);
        }

        while(!q_indegree_0.empty()) {
            int cur = q_indegree_0.front(); q_indegree_0.pop();
            int nxt = favorite[cur];
            depth[nxt] = max(depth[nxt], depth[cur]+1);
            if(--in_degree[nxt] == 0) 
                q_indegree_0.push(nxt);
        }

        int max_length = 0, max_cycle = 0;
        for(int i = 0; i < n; ++i) {
            if(in_degree[i] == 0) continue;
            int cur = i, cur_cycle = 0;
            while(in_degree[cur]) {
                in_degree[cur] = 0;
                ++cur_cycle;
                cur = favorite[cur];
            }
            if(cur_cycle == 2) {
                max_length += depth[i] + depth[favorite[i]];
            } else {
                max_cycle =  max(max_cycle, cur_cycle);
            }
        }

        return max(max_length, max_cycle);
    }
};


class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<int>indegree(n);
        queue<int>q;
        //unordered_map<int,unordered_set<int>>graph;
        for(int i = 0; i < n; ++i){
            //graph[favorite[i]].insert(i);
            ++indegree[favorite[i]];
        }
        for(int i = 0; i < n ; ++i) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        vector<int>max_child_count(n, 1);
        while(!q.empty()){
            int cur = q.front(); q.pop();
            int nxt = favorite[cur];
            max_child_count[nxt] = max(max_child_count[nxt], max_child_count[cur]+1);
            if(--indegree[nxt] == 0) {
                q.push(nxt);
            }
        }
        int max_single_cycle = 0, max_length = 0; 
        for(int i = 0; i < n; ++i){
            if(indegree[i]!=0) {
                int cur = i;
                int cur_cycle_count = 0;
                while(indegree[cur]){
                    indegree[cur] = 0;
                    ++cur_cycle_count;
                    cur = favorite[cur];
                }
                if(cur_cycle_count == 2) {
                    //cout<< " i "<<i<<" max_child_count[i] "<<max_child_count[i]<<" max_child_count[favorite[i]] "<<max_child_count[favorite[i]]<<endl;
                    max_length += max_child_count[i] + max_child_count[favorite[i]];
                } else {
                    max_single_cycle = max(max_single_cycle, cur_cycle_count);
                }
            }
        }
        //cout<<" max_single_cycle "<<max_single_cycle<<" max_length "<< max_length << endl;
        return max(max_single_cycle, max_length);
    }
};






class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        unordered_map<int,unordered_set<int>> graph;
        int n = favorite.size();
        for(int i = 0 ; i<n; ++i){
            if(favorite[favorite[i]]!=i)
                graph[favorite[i]].insert(i);
        }
        vector<int> visited(n,0);
        auto dfs = [&](this auto && dfs, int cur)->int{
            visited[cur] = true;
            int res = 1;
            for(auto nxt: graph[cur]){
                res = max(res, dfs(nxt)+1);
            }
            return res;
        };
        
        int res = 0;
        //look up any cycle of 2
        for(int i = 0; i<n; ++i){
            if(favorite[favorite[i]] == i && visited[i] == 0) {
                //distance[i] == 0 avoid double count
                res += dfs(i) + dfs(favorite[i]);
            }
        }

        for(int i = 0; i<n; ++i){
            if(visited[i] ) continue;
            int cur = i;
            int cur_cycle = 0;
            while(visited[cur] == 0) {
                //cout<<" i "<<i<<" cur "<<cur << " cur_cycle "<<cur_cycle<<" nxt "<<favorite[cur]<<endl;
                visited[cur] = 1;
                ++cur_cycle;
                cur = favorite[cur];
            }
            for(int k = i; k!=cur; k=favorite[k]){
                //这是减去cycle头部 比如
                // 1 -> 2 -> 3 -> 4 -> 5 - > 6 -> 3
                // cur = 3, cur_cycle之前是6，直到k = 3, cur_cycle变为4

                --cur_cycle;
            }
            res = max(res, cur_cycle);
            
        }
        return res;
    }
};