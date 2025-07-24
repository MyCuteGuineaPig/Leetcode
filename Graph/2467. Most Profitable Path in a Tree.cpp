class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        unordered_map<int,int>bob_map;
        unordered_set<int>visited;
        unordered_map<int, unordered_set<int>>graph;
        for(auto& e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        auto dfs = [&](this auto&& dfs, int cur, int steps) -> bool {
            bob_map[cur] = steps;
            if (cur == 0) {
                return true;
            }
            visited.insert(cur);
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    if(dfs(nxt, steps + 1)) {
                        return true;
                    }
                }
            }
            bob_map.erase(cur);
            return false;
        };
        dfs(bob, 0);
        
        visited.clear();
        auto dfs_0 = [&](this auto&& dfs_0, int cur, int steps) -> int {
            int reward = 0;
            if(bob_map.count(cur)){
                if(bob_map[cur] > steps) {
                    reward = amount[cur];
                } else if (bob_map[cur] == steps) {
                    reward = amount[cur] / 2;
                } 
            } else {
                reward = amount[cur];
            }
            visited.insert(cur);
            int nxt_reward = numeric_limits<int>::min();
            bool isLeaf = false;
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    nxt_reward = max(nxt_reward, dfs_0(nxt, steps+1));
                    isLeaf = true;
                }
            }
            //cout<<" cur "<<cur<<" step "<<steps << " reward " << reward << " nxt_reward "<<nxt_reward<< endl;
            return reward + (isLeaf ? nxt_reward: 0);
        };
        return dfs_0(0, 0);
    }
};


class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        unordered_map<int,int>bob_map;
        unordered_set<int>visited;
        unordered_map<int, unordered_set<int>>graph;
        for(auto& e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        auto dfs = [&](this auto&& dfs, int cur, int steps) -> bool {
            bob_map[cur] = steps;
            if (cur == 0) {
                return true;
            }
            visited.insert(cur);
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    if(dfs(nxt, steps + 1)) {
                        return true;
                    }
                }
            }
            bob_map.erase(cur);
            return false;
        };
        dfs(bob, 0);
        
        visited.clear();
        queue<tuple<int,int, int>> q; 
        q.push({0, 0, 0});
        int max_reward = numeric_limits<int>::min();
        while(!q.empty()) {
            auto [cur, steps, reward] =  q.front(); q.pop();
            //cout<< " cur "<<cur << " steps "<<steps << " reward "<<reward<<endl;
            visited.insert(cur);
            if(bob_map.count(cur)){
                if(bob_map[cur] > steps) {
                    reward += amount[cur];
                } else if (bob_map[cur] == steps) {
                    reward += amount[cur] / 2;
                } 
            } else {
                reward += amount[cur];
            }
            if(graph[cur].size() == 1 && cur != 0) {
                max_reward = max(max_reward, reward);
            }
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    q.push({nxt, steps + 1, reward});
                }
            }
        }
        return max_reward;
    }
};


class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob,
                           vector<int>& amount) {
        n = amount.size();
        tree.resize(n, vector<int>());

        // Form tree with edges
        for (vector<int> edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        distanceFromBob.resize(n);
        return findPaths(0, 0, 0, bob, amount);
    }

private:
    vector<vector<int>> tree;
    vector<int> distanceFromBob;
    int n;

    // Depth-first Search
    int findPaths(int sourceNode, int parentNode, int time, int bob,
                  vector<int>& amount) {
        int maxIncome = 0, maxChild = INT_MIN;

        // Find the node distances from Bob
        if (sourceNode == bob)
            distanceFromBob[sourceNode] = 0;
        else
            distanceFromBob[sourceNode] = n;
        for (int adjacentNode : tree[sourceNode]) {
            if (adjacentNode != parentNode) {
                maxChild = max(maxChild, findPaths(adjacentNode, sourceNode,
                                                   time + 1, bob, amount));
                distanceFromBob[sourceNode] =
                    min(distanceFromBob[sourceNode],
                        distanceFromBob[adjacentNode] + 1);
            }
        }
        // Alice reaches the node first
        if (distanceFromBob[sourceNode] > time) maxIncome = amount[sourceNode];

        // Alice and Bob reach the node at the same time
        else if (distanceFromBob[sourceNode] == time)
            maxIncome = amount[sourceNode] / 2;

        // Return max income of leaf node
        if (maxChild == INT_MIN)
            return maxIncome;
        else
            return maxIncome + maxChild;
    }
};


class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        vector<int>bob_path(n, n);
        unordered_set<int>visited;
        unordered_map<int, unordered_set<int>>graph;
        for(auto& e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        auto dfs = [&](this auto&& dfs, int cur)



        auto dfs = [&](this auto&& dfs, int cur, int steps) -> bool {
            bob_map[cur] = steps;
            if (cur == 0) {
                return true;
            }
            visited.insert(cur);
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    if(dfs(nxt, steps + 1)) {
                        return true;
                    }
                }
            }
            bob_map.erase(cur);
            return false;
        };
        dfs(bob, 0);
        
        visited.clear();
        queue<tuple<int,int, int>> q; 
        q.push({0, 0, 0});
        int max_reward = numeric_limits<int>::min();
        while(!q.empty()) {
            auto [cur, steps, reward] =  q.front(); q.pop();
            cout<< " cur "<<cur << " steps "<<steps << " reward "<<reward<<endl;
            visited.insert(cur);

            if(bob_map.count(cur)){
                if(bob_map[cur] > steps) {
                    reward += amount[cur];
                } else if (bob_map[cur] == steps) {
                    reward += amount[cur] / 2;
                } 
            } else {
                reward += amount[cur];
            }
            if(graph[cur].size() == 1 && cur != 0) {
                max_reward = max(max_reward, reward);
            }
            for(auto& nxt: graph[cur]){
                if(!visited.count(nxt)){
                    q.push({nxt, steps + 1, reward});
                }
            }
        }
        return max_reward;
    }
};