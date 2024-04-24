/*
比如 

0 (1) ->  1 (1) ->  2 (2) -> 3 (2)
                    |
                    v
                    4 (3)

    [Counter({1: 1}), Counter({1: 1}), Counter({2: 1}), Counter({2: 1}), Counter({3: 1})]
当 0->1 更新
    [Counter({1: 2}), Counter({1: 1}), Counter({2: 1}), Counter({2: 1}), Counter({3: 1})]
当 1->2 更新  =》 1 的parent 是 0,
    [Counter({2: 1}), Counter({1: 1}), Counter({2: 1}), Counter({2: 1}), Counter({3: 1})]


*/


class Solution {
public:
    int find(vector<int>&p, int x){
        return p[x] == x ? x : p[x] = find(p, p[x]);
    } 

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n  = vals.size();
        int res = n;
        //cout<<" res "<<res<<endl;
        vector<pair<int,int>>counter(n);
        vector<vector<int>> paths;
        vector<int>parents(n);
        iota(parents.begin(), parents.end(), 0);
        for(auto & e: edges){
            paths.push_back({max(vals[e[0]], vals[e[1]]), e[0], e[1]});
        }
        sort(paths.begin(), paths.end());

        for(int i = 0; i < vals.size(); ++i){
            counter[i] = {vals[i], 1};
        }

        
        for(auto & path: paths){
            int val = path[0], x = path[1], y = path[2];
            int px = find(parents, x), py = find(parents, y);
            int cx = 0, cy = 0;
            if(counter[px].first == val){
                cx = counter[px].second;
            }
            if(counter[py].first == val){
                cy = counter[py].second;
            }
            res += cx * cy;
            //cout<<" x "<<x<< " y "<<y<<" px "<<px<<" py "<<py<<"  cx "<<cx<<" cy "<<cy<<endl;
            parents[py] = px;
            counter[px] = {val, cx + cy};
        }
        return res;
    }
};


class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void union_set(int x, int y) {
        int xset = find(x), yset = find(y);
        if (xset == yset) {
            return;
        } else if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        } else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        } else {
            parent[yset] = xset;
            rank[xset]++;
        }
    }
};

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        // Mapping from value to all the nodes having the same value in non-descending order of values.
        map<int, vector<int>> valuesToNodes;
        for (int node = 0; node < n; node++) {
            valuesToNodes[vals[node]].push_back(node);
        }

        UnionFind dsu(n);
        int goodPaths = 0;

        // Iterate over all the nodes with the same value in sorted order, starting from the lowest
        // value.
        for (auto& [value, nodes] : valuesToNodes) {
            // For every node in nodes, combine the sets of the node and its neighbors into one set.
            for (int node : nodes) {
                for (int neighbor : adj[node]) {
                    // Only choose neighbors with a smaller value, as there is no point in
                    // traversing to other neighbors.
                    if (vals[node] >= vals[neighbor]) {
                        dsu.union_set(node, neighbor);
                    }
                }
            }
            // Map to compute the number of nodes under observation (with the same values) in each
            // of the sets.
            unordered_map<int, int> group;
            // Iterate over all the nodes. Get the set of each node and increase the count of the
            // set by 1.
            for (int u : nodes) {
                group[dsu.find(u)]++;
            }
            // For each set of "size", add size * (size + 1) / 2 to the number of goodPaths.
            for (auto& [_, size] : group) {
                goodPaths += (size * (size + 1) / 2);
            }
        }
        return goodPaths;
    }
};




