class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        unordered_map<int, unordered_set<int>> graph;
        vector<int>degree(n);
        int remaining_nodes = n; 
        for(auto& edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        queue<int>q;
        //remove tree which doesn't have coin 
        for(int i = 0; i < n; ++i) {
            if(degree[i] == 1 && coins[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            --remaining_nodes; 
            int top = q.front(); q.pop();
            for(auto nxt: graph[top]) {
                if(--degree[nxt] == 1 && coins[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            if(degree[i] == 1 && coins[i] == 1){
                q.push(i);
            }
        }

        //remove tree which have coin within step of 2
        for(int step = 0; step < 2; ++step){
            int size = q.size();
            while(size--) {
                --remaining_nodes; 
                int top = q.front(); q.pop();
                for(auto nxt: graph[top]) {
                    if(--degree[nxt] == 1) {
                        q.push(nxt);
                    }
                }
            }
        }

        return max(0, 2*(remaining_nodes-1));
    }
};

/*


Why (remainingNodes - 1) * 2?

因为要回到起点，所以每条边都要走两次。 n 个nodes 需要 n-1 条边来连接它们。 往返就是 2*(n-1)。

A fundamental property of trees is that if you have $V$ nodes, you have exactly $V-1$ edges.
If your "peeling" process leaves you with a core of 3 nodes, those 3 nodes are connected by 2 edges. 
To visit all of them and return to your starting vertex, you must travel:

1. Across Edge A
2. Across Edge B
3. Back across Edge 
4,Back across Edge ATotal: 4 steps 2 edges *2.I

f the peeling process removes everything (leaving 1 or 0 nodes), 
the answer is 0 because you are already within distance 2 of all coins and do not need to move to collect them.
*/



class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        queue<int> q;
        // 1. Remove leaves with no coins
        for (int i = 0; i < n; i++) {
            while (degree[i] == 1 && coins[i] == 0) {
                // This is slightly simplified: in a real implementation, 
                // you'd use a queue to handle the "ripple effect" properly.
            }
        }
        
        // Standard Topological Sort approach to trimming:
        queue<int> leafQ;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1 && coins[i] == 0) leafQ.push(i);
        }

        int remainingNodes = n;
        while (!leafQ.empty()) {
            int u = leafQ.front(); leafQ.pop();
            remainingNodes--;
            for (int v : adj[u]) {
                if (--degree[v] == 1 && coins[v] == 0) leafQ.push(v);
            }
        }

        // 2. Peel two layers of leaves (the ones with coins)
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1 && coins[i] == 1) leafQ.push(i);
        }

        for (int step = 0; step < 2; step++) {
            int size = leafQ.size();
            while (size--) {
                int u = leafQ.front(); leafQ.pop();
                remainingNodes--;
                for (int v : adj[u]) {
                    if (--degree[v] == 1) leafQ.push(v);
                }
            }
        }

        // Each edge between remaining nodes is traversed twice.
        // In a tree, Edges = Nodes - 1.
        return max(0, (remainingNodes - 1) * 2);
    }
};