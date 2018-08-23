/*
685. Redundant Connection II

In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. 
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Example 3:
Input: [[2,1],[3,1],[4,2],[1,4]]
Output: [2,1]
    2-> 1 <- 3
    ^   
    |   |
    4 <- 
不能移除[1,4] 因为 2的child 和3的child 都是1不可以的

Example 4: 
Input: [[4,2],[1,5],[5,2],[4,3],[4,1]]
Output: [5:2] 
    3 <-- 4 --> 1 
          |     |
          v     v
          2 <-- 5
*/


0 parent 0
1 parent 3
2 parent 3
3 parent 3
4 parent 3
5 parent 3

/*
3 种情况:
- No-Cycle, but 2 parents pointed to one same child
- No dup parents but with Cycle
- Possessing Cycle and dup-parents
*/

/*
 定义： 1 -> 4, 1 是parent, 4 是child
先找潜在的 一个child 有两个parent 的情况, 然后去掉一个parent(这里去掉后出现的，(前出现后出现都可以))，  edge[1] = 0
dup[0] = 没有去掉的node, dup[1] = 去掉的node, dup[0], dup[1] 的child是一样的, parent 不一样
这样做目的：
1. 去掉一个parent后，不可以构成cycle，这样最后return 去掉的node
    [1,4], [1,5], [4,3], [2,4], [5,2]]
    3 <-- 4 --> 1    变成    3 <-- 4 --> 1     return [5,2]
          |     |                  |     |
          v     v                  v     v
          2 <-- 5                  2     5
2 去掉之后还有cycle, 表示没有去掉的可以构成cycle，还原去掉的，eliminate没有的去掉的, 可以构成tree, return没有去掉的node dup[0]
    [[4,1], [2,4] [1,5], [5,2], [3,4]]
    
    3 --> 4 --> 1    变成    3     4 <-- 1     return [2, 4]
          ^     |                  ^     |
          |     v                  |     v
          2 <-- 5                  2  <- 5

3. 有duplicate, 但是没有cycle， return last one 就是duplicate back()
    [[1,4], [1,5], [4,3], [2,4]]
    3 <-- 4 <-- 1    变成    3 <-- 4 <-- 1     return [2, 4]
          ^     |                  ^     |
          |     v                  |     v
          2     5                  2     5

4. 没有duplicate， 有cycle，remove last one 构成cycle的
    [[1,4], [1,3], [3,2], [2,4]]
          4 <-- 1    变成           4 <-- 1     return [2, 4]
          ^     |                  ^     |
          |     v                  |     v
          2 <-- 3                  2  <- 3

simple logic: 
1) Check whether there is a node having two parents. 
    If so, store them as candidates A and B, and set the second edge invalid. 
2) Perform normal union find. 
    If the tree is now valid 
           simply return candidate B
    else if candidates not existing 
           we find a circle, return current edge; 
    else 
           remove candidate A instead of B.

*/

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        DisjointSet ds(edges.size());
        unordered_map<int,int>parent;
        vector<vector<int>>dup;
        for(auto& edge: edges){
            if(parent[edge[1]]!= 0){
                dup.push_back({parent[edge[1]], edge[1]});
                dup.push_back(edge);
                edge[1] = 0; //把一个child 有两个parent的情况eliminate 一个parent
            }else{
                parent[edge[1]] = edge[0];
            }
        }
        for(auto edge: edges){
            if(edge[1] == 0) continue;
            if(ds.join(edge[0], edge[1])){
                if(dup.empty())
                    return edge;
                return dup.front();
            }
        }
        return dup.back();
    }

private:
    struct DisjointSet{
        vector<int>child;
        DisjointSet(int size){
            child.resize(size+1);
            iota(child.begin(), child.end(),0);
        }

        int find(int x){
            return child[x] == x ? x: child[x] = find(child[x]);
        }

        bool join(int a, int b){
            int roota = find(a), rootb = find(b);
            if(roota == rootb) return true;
            child[roota] = rootb;
            return false;
        }

    };
};

class Solution {
public:
  vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        vector<int> root(n+1, 0), c1, c2;
        for (auto &e:edges) {
            if (root[e[1]]==0) root[e[1]]=e[0];
            else {
                c1={root[e[1]], e[1]};
                c2=e;
                e[1]=0;
            }
        }
        for (int i=1; i<=n; i++) root[i]=i;
        for (auto e:edges) {
            if (e[1]==0) continue;
            int x=findRoot(root, e[0]);
            int y=findRoot(root, e[1]);
            if (x==y) {
                if (c1.empty()) return e;
                else return c1;
            }
            root[y]=x;
        }
        return c2;
       
    }
    int findRoot(vector<int>& parent, int k) {
        while (parent[k] != k) k=parent[k];
        return k;
    }
};

/*
first 表示第一个重复node 的
second 表示第二个重复node的
first second的child 一样的

last 表示构成cycle的链

continue 相当于 间接删除了第二node 的链
如果有first, second 没有last，1. 表示删除链删对了，return edges[second]， 2. 或者表示本来也没有cycle的链，只有重复的，根据题目要求，返回第二个也是最后重复的链
如果没有first, second， 有last, 表示没有重复的链 只有循环的链，返回edges[last] 构成循环的链即可
如果既有first, second, 也有last 表示删除链删错了，return 没有删除的链 edges[first]
*/
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int>parent(n, -1), ds(n);
        iota(ds.begin(),ds.end(),0);
        int first = -1, second = -1, last = -1; //first second 表示重复的, last 的表示cycle的
        for(int i = 0; i < n; i++) {
            int p = edges[i][0]-1, c = edges[i][1]-1;
            if (parent[c] != -1) {
                first = parent[c];
                second = i;
                continue;
            }
            parent[c] = i;
            
            int p1 = find(ds, p), p2 = find(ds, c);
            if (p1 == p2) last = i;
            else ds[p2] = p1;
        }
        if (last == -1) return edges[second]; // no cycle found by removing second
        if (second == -1) return edges[last]; // no edge removed
        return edges[first];
    }
    
    int find(vector<int>&ds, int i) {
        return ds[i] == i ? i : (ds[i] = find(ds, ds[i]));
    }
};



class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int>parent(n+1, -1), ds(n+1);
        int first = -1, second = -1, last = -1; //first second 表示重复的, last 的表示cycle的
        for(int i = 0; i < n; i++) {
            int p = edges[i][0], c = edges[i][1];
            if (parent[c] != -1) {
                first = parent[c];
                second = i;
                continue;
            }
            parent[c] = i;
            
            int p1 = find(ds, p);
            if (p1 == c) last = i;
            else ds[c] = p1;
        }

        if (last == -1) return edges[second]; // no cycle found by removing second
        if (second == -1) return edges[last]; // no edge removed
        return edges[first];
    }
    
    int find(vector<int>&ds, int i) {
        return ds[i] == 0 ? i : (ds[i] = find(ds, ds[i]));
    }
};


/* 

DFS, 用adj 表示所有的通道，
dup 表示child有两个parent的中其中一个通道, cycle 表示构成循环的最后的一个edge

1， 如果没有duplicate, 只有cycle 返回cycle
2.  如果没有cycle, 只有duplicate, 返回duplicate
3.  既有cycle又有duplicate , 看现在duplicate 是不是valid, 如果valid 返回，不valid 找到valid的

比如, 
     3 --> 4 --> 1    return [2,4], 假如现在dup 是 [3,4] 那么4作为起点，找最后一个edge, 直到经过的点是visited 
          ^     |                 
          |     v                 
          2 <-- 5                 


*/
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        DisjointSet ds(edges.size());
        unordered_set<int>hasparent;
        vector<vector<int>>adj(edges.size()+1);
        vector<int>dup, cycle;
        for(auto& edge: edges){
            adj[edge[0]].push_back(edge[1]);
            if(hasparent.count(edge[1])){
                dup = edge;
            } else hasparent.insert(edge[1]);
            if(ds.join(edge[0], edge[1])){
                cycle = edge;
            }
        }
        if(dup.empty()) return cycle;
        if(cycle.empty()) return dup;
        vector<int>can = ds.detectCycle(dup[1], adj);
        return can[1] == -1 ? dup : can;
    }

private:
    struct DisjointSet{
        vector<int>child;
        vector<int>visited;
        DisjointSet(int size){
            child.resize(size+1);
            visited.resize(size+1);
            iota(child.begin(), child.end(),0);
        }

        int find(int x){
            return child[x] == x ? x: child[x] = find(child[x]);
        }

        bool join(int a, int b){
            int roota = find(a), rootb = find(b);
            if(roota == rootb) return true;
            child[roota] = rootb;
            return false;
        }

        vector<int> detectCycle(int x, const vector<vector<int>>adj){
            visited[x] = true;
            for(int i = 0; i<adj[x].size(); i++){
                if(visited[adj[x][i]]) return {x, adj[x][i]};
                return detectCycle(adj[x][i], adj);
            }
            return {-1,-1};
        }

    };
};





class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<vector<int>> parent(edges.size(), vector<int>());
        vector<bool> visited(edges.size(), false);
        vector<int> cycle{-1, -1};
        int id_two_parents = -1;
        for (auto &e : edges) {
            if (visited[e[0]] && visited[e[1]]) 
                cycle = {e[0], e[1]};
            visited[e[0]] = true;
            visited[e[1]] = true;
            parent[e[1]].push_back(e[0]);
            if (parent[e[1]].size() > 1)
                id_two_parents = e[1];
        }
        //
        if (id_two_parents < 0) {
            // no node has two parents, means a single cycle, any node in this cycle can be root
            // so return the last cycle edge
            return cycle;
        } else {
            // one node has two parents, must remove one edge from there.
            // we recursively find the parent, 
            // if the last node has no parent, that's the root, we should keep this branch
            // otherwise if this branch is cycle, remove this edge.
            int branch0 = parent[id_two_parents][0];
            int branch1 = parent[id_two_parents][1];
            int id = branch0;
            while (parent[id].size() != 0 && prarent[id] != id_two_parents) {
                // find the root or the cycle
                id = parent[id];
            }
            if (id == id_two_parents) {
                // this is the cycle branch, remove this branch
                return {branch0, id_two_parents};
            } else {
                // parent[id].size() == 0, the root branch, remove the other branch
                return {branch1, id_two_parents};
            }
        }
    }
};