/*
684. Redundant Connection

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), 
with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, 
that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, 
return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.



*/


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n  = edges.size();
        vector<int>parent(n+1);
        iota(parent.begin(), parent.end(), 0);
        
        auto f = [&](this auto&& f, int i) -> int{
            return parent[i] == i ? i : parent[i] = f(parent[i]);
        };
        vector<int>res; 
        for(auto edge: edges) {
            int i = edge[0], j = edge[1];
            int p1 = f(i), p2 = f(j);
            if(p1 == p2) res = edge; 
            else parent[p1] = p2;
        }
        return res;
    }
};



class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n  = edges.size();
        unordered_map<int, unordered_set<int>>graph;
        for(auto edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        
        vector<int>visited(n+1);
        vector<int>cycle(n+1);
        auto dfs = [&](this auto&& dfs, int cur, int par) -> int {
            visited[cur] = true;
            for(auto nxt: graph[cur]){
                if(!visited[nxt]) {
                    int res = dfs(nxt, cur);
                    if (res > 0) {
                        cycle[cur] = 1;
                        return cur == res ? -1: res;
                    }
                } else if (nxt != par) {
                    cycle[cur] = 1;
                    return nxt;
                }
            }
            return -1;
        };

        dfs(1, -1);

        for(int i = edges.size() -1; i >= 0; --i)
            if(cycle[edges[i][0]] && cycle[edges[i][1]])
                return edges[i];
        return {};
    }
};




class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n  = edges.size();
        unordered_map<int, unordered_set<int>>graph;
        vector<int>degree(n+1);
        for(auto edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }
        queue<int>q; 
        for(int i = 1; i<=n; ++i) {
            if(degree[i] == 1) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto nxt: graph[cur]){
                if(--degree[nxt] == 1) 
                    q.push(nxt);
            }
        }
        for(int i = edges.size() -1; i>=0; --i){
            if(degree[edges[i][0]] > 1 && degree[edges[i][1]] > 1)
                return edges[i];
        }
        
        return {};
    }
};
/*

UnionFind, 如果union 后发现两个parent 在join 之前已经是一样的，表示已经有路连接两个edge，两个edge 再连接肯定是cycle


*/


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DisjointSet ds(edges.size());
        vector<int>res;
        for(auto edge: edges){
            if(ds.join(edge[0]-1,edge[1]-1))
                res = edge;
        }
        return res;
    }

private:
    struct DisjointSet{
        vector<int>parent;
        DisjointSet(int size){
            parent.resize(size);
            iota(parent.begin(), parent.end(),0);
        }  
        
        int find(int i){
            return parent[i] == i ?  i : parent[i] = find(parent[i]);
        }
        
        bool join(int a, int b){
            int roota = find(a), rootb = find(b);
            if(roota == rootb) return true;
            parent[max(roota, rootb)] = min(roota, rootb);
            return false;
        }
    };
};



class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DisjointSet ds(edges.size());
        vector<int>res;
        for(auto edge: edges)
            if(ds.join(edge[0]-1,edge[1]-1))
                return edge;
        return res;
    }

private:
    struct DisjointSet{
        vector<int>parent;
        DisjointSet(int size){
            parent.resize(size);
            iota(parent.begin(), parent.end(),0);
        }  
        
        int find(int i){
            return parent[i] == i ?  i : parent[i] = find(parent[i]);
        }
        
        bool join(int a, int b){
            int roota = find(a), rootb = find(b);
            if(roota == rootb) return true;
            parent[roota] = rootb;
            return false;
        }
    };
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> res;
        vector<int> parent;
        parent.reserve(edges.size());
        for(int i=0; i< edges.size(); ++i) {
            parent[i] = i+1;
        }
        for(vector<int>& edge : edges) {
            if(Find(edge[0], parent)==Find(edge[1], parent)) {
                res.push_back(edge[0]);
                res.push_back(edge[1]);
                return res;
            } else {
                Union(edge[0], edge[1], parent);
            }
        }
        return res;
    }
    
    int Find(int x, vector<int>& parent) {
        int par = x;
        while(parent[par-1]!=par) {
            parent[par-1] = parent[parent[par-1]-1];
            par = parent[par-1];
        }
        return par;
    }
    
    void Union(int a, int b, vector<int>& parent){
        parent[Find(a, parent)-1] = Find(b, parent);
    }
};



/*
Although union-find is a natural fit to this problem,
I find there is another way to tackle this problem which is also intuitive and easy to understand. 
That is, we can recursively remove leaf nodes from the graph to uncover the cycle existing in the graph. 
A leaf node in an undirected graph is defined as a node that is has only one adjacent neighbor. 
For example, consider the following graph:

           1 ——— 2 
            \   /
              3 —— 4
node 4 would be a leaf node.
Before removing the leaf node, the graph is:
1: 2, 3
2: 1,3
3: 1,2,4
4: 3
Before removing the leaf node, the graph becomes:
1: 2, 3
2: 1,3
3: 1,2
*/


class Solution {
private:
  void uncoverCycle(unordered_map<int, unordered_set<int>>& graph) {
    int n = graph.size();
    vector<int> remove = {};
    for (auto& kv : graph) {
      int node = kv.first;
      auto& adjlist = kv.second;
      if (adjlist.size() == 1) { // leaf node
        remove.push_back(node);
        auto it = adjlist.begin();
        graph[*it].erase(node);
      }
    }

    if (remove.empty()) return;
    else {
      for (int node : remove) graph.erase(node);
      uncoverCycle(graph);
    }
  }

public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    unordered_map<int, unordered_set<int>> graph;
    for (int i = 0; i < n; ++i) { // undirected graph
      graph[edges[i][0]].insert(edges[i][1]);
      graph[edges[i][1]].insert(edges[i][0]);
    }

    // recursively remove leaf nodes to uncover the cycle
    uncoverCycle(graph);

    for (int i = n - 1; i >= 0; --i) {
      if (graph.count(edges[i][0]) && graph.count(edges[i][1])) return edges[i];
    }

    return {};
  }
};