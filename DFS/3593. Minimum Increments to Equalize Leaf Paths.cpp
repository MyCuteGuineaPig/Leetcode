/*
思路： 保持当前情况，每个节点需要更改的次数

只能更改点 匹配当前最大path value 比如 
                  
                    5
                  /   \
                2        10
            / |  |  \  
           1  1  1  7       

           比如更改2 点来减少1 改变次数，但一旦2变成9, (5+9 + 1 = 15 max 值) ， 7就不能满足, 所以只能更改两边的1
*/
class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        unordered_map<int, unordered_set<int>>mp;
        for(const auto& e: edges){
            mp[e[0]].insert(e[1]);
            mp[e[1]].insert(e[0]);
        }
        long res = 0;
        auto dfs = [&](this auto&& dfs, int cur, int parent) -> long{ //first cur_max, second count
            unordered_map<long,int>scores_count; //key must be long
            long max_score = 0;
            for(auto nxt: mp[cur]){
                if (nxt == parent) 
                    continue;
                auto child_cost = dfs(nxt, cur);
                scores_count[child_cost] += 1;
                max_score = max(max_score, child_cost);
            }
            for(auto it: scores_count){
                res += (it.first == max_score? 0: it.second);
            }
            
            return max_score + cost[cur];
            
        };
        dfs(0, 0);
        return res;
    }
};


class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        unordered_map<int, unordered_set<int>>mp;
        for(const auto& e: edges){
            mp[e[0]].insert(e[1]);
            mp[e[1]].insert(e[0]);
        }
        long res = 0;
        auto dfs = [&](this auto&& dfs, int cur, int parent) -> long{ //first cur_max, second count
            //cout<<" cur "<<cur<<" parent "<<parent<<endl;
            unordered_map<long,int>scores_count; //key must be long
            long max_score = 0;
            int total_child = 0, max_child_count = 0;
            for(auto nxt: mp[cur]){
                if (nxt == parent) 
                    continue;
                auto child_cost = dfs(nxt, cur);
                if (max_score < child_cost){
                    max_child_count = 1;
                    max_score = child_cost;
                } else if (max_score == child_cost) {
                    ++max_child_count;
                }
                ++total_child;
            }
            res += (total_child-max_child_count);
            return max_score + cost[cur];
            
        };
        dfs(0, 0);
        return res;
    }
};



class Solution {
public:
    // DFS returns max path sum from this node to a leaf
    long long dfs(int node, int parent, int& operations, vector<vector<int>>& adj, vector<int>& cost) {
        long long maxChildSum = 0;
        int childCount = 0, maxCount = 0;

        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;

            long long childSum = dfs(neighbor, node, operations, adj, cost);
            if (childSum > maxChildSum) {
                maxChildSum = childSum;
                maxCount = 1;
            } else if (childSum == maxChildSum) {
                maxCount++;
            }
            childCount++;
        }

        operations += (childCount - maxCount);
        return cost[node] + maxChildSum;
    }

    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int operations = 0;
        dfs(0, -1, operations, adj, cost);
        return operations;
    }
};


class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        unordered_map<int, unordered_set<int>>mp;
        for(const auto& e: edges){
            mp[e[0]].insert(e[1]);
            mp[e[1]].insert(e[0]);
        }
        auto dfs = [&](this auto&& dfs, int cur, int parent) -> tuple<long,int>{ //first cur_max, second count
            if (mp[cur].size() == 1 && *mp[cur].begin() == parent) {
                return {cost[cur], 0};
            }
            unordered_map<int,int>scores_count;
            int res = 0;
            long max_score = -1;
            for(auto nxt: mp[cur]){
                if (nxt == parent) continue;
                auto [child_cost, child_res] = dfs(nxt, cur);
                scores_count[child_cost] += 1;
                max_score = max(max_score, child_cost);
                res += child_res;
            }
            //mp[cur].size() 是有几个edge to other nodes including to parent
            //only root (cur==parent) doesn't has the edge to parent
            return {max_score + cost[cur], res + mp[cur].size() - (cur != parent) -  scores_count[max_score] };
            
        };
        auto [_, res] = dfs(0, 0);
        return res;
    }
};