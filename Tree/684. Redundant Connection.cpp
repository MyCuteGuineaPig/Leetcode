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




class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N=edges.size();
        vector<int> res, root(N+1, 0);
        for (int i=1; i<=N; i++) root[i]=i;
        for (auto edge : edges) {
            int x=find(edge[0], root), y=find(edge[1], root);
            if(x!=y) root[x]=y;
            else res=edge;
        }
        return res;
    }
    int find(int i, vector<int>& root) {
        while(root[i]!=i) {
            root[i]=root[root[i]];
            i=root[i];
        }
        return i;
        //return root[i]==i ? i : find(root[i], root);
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