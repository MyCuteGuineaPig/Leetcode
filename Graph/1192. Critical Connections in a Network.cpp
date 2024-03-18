class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> graph[n];
        for (auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        int ranks[n];
        fill_n(ranks, n, NO_RANK);
        vector<vector<int>> result;
        // Because whole graph is connected, there is no need to loop through every node.
        criticalConnections(graph, n, 0, 0, ranks, result);        
        
        return result;
    }
private:
    static const int NO_RANK;

    int criticalConnections(vector<int> graph[], int n, int node, int myRank, int ranks[], vector<vector<int>>& result) {
        if (ranks[node] != NO_RANK) {
            return ranks[node];
        }

        int lowestRank = myRank;
        ranks[node] = myRank;
        for (auto neighbor : graph[node]) {
            if (ranks[neighbor] == myRank - 1 || ranks[neighbor] == n) {
                // ranks[neighbor] == myRank - 1:
                // Do not go back immediately to parent, this will lead to
                // parent-child-parent circle immediately.
                // This is why NO_RANK is set to -2 instead of -1, because the first node of a recursion has myRank 0.
                //
                // ranks[neighbor] == n:
                // Do not include node=>neighbor in the result. Reason:
                // This can be explained from a couple of aspects:
                // - This means neighbor has been finished, so neighbor=>node has been decided before neighbor is finished,
                //   and if neighbor=>node is already decided, we don't need to make a decision on node=>neighbor because
                //   it is undirected graph.
                // - When neighbor=>node was decided, the decision must be "not include it in the result", because
                //   node is an ancestor of neighbor, so neighbor=>node is a back edge, meaning at that time it already
                //   detected that there is a cycle between neighbor and node, so that edge would not be included in the result.
                continue;
            }
            
            int neighborRank = criticalConnections(graph, n, neighbor, myRank + 1, ranks, result);
            lowestRank = min(lowestRank, neighborRank);
            if (neighborRank > myRank) {
                result.push_back({min(node, neighbor), max(node, neighbor)});
            }
            
        }
        
        ranks[node] = n;
        return lowestRank;
    }
};

const int Solution::NO_RANK = -2;





class Solution {
public:
    int dfs(vector<int>&rank, vector<unordered_set<int>>&graph, vector<vector<int>>&res, int cur, int depth, int n){
        if(rank[cur] >= 0){
            return rank[cur];
        }
        rank[cur]= depth;
        int minimum_depth = depth;
        vector<int>;
        for(auto next: graph[cur]){
            if(rank[next] == depth - 1){
                continue;
            }
            int parent_depth = dfs(rank, graph, res, next, depth + 1, n);
            //cout<<" [get ] cur="<< cur<<" next= "<<next<<" parent_depth= "<<parent_depth<<" cur depth="<<depth<<endl;
            if (parent_depth > depth){
                res.push_back({cur, next});
            }
            minimum_depth = min(minimum_depth, parent_depth);
        }
        rank[cur]= minimum_depth;//需要这个比如 1->2 2->3, 1->3 如果没有这行, rank[3] = 3， 当1->3, 返回的是depth=3, 而真实的是2
        return minimum_depth;
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<unordered_set<int>>graph(n);
        for(int i = 0; i<connections.size(); ++i){
            graph[connections[i][0]].insert(connections[i][1]);
            graph[connections[i][1]].insert(connections[i][0]);
        }
        vector<int>rank(n, -2);
        vector<vector<int>> res;
        dfs(rank, graph, res, connections[0][0], 0, n);
        return res;
    }
};



class Solution {
public:
    int dfs(vector<vector<pair<int,int>>>&graph, vector<int>&critial, vector<int>&rank, int depth, int parent, int cur){
        if(rank[cur] != -1) {
            return rank[cur];
        }
        rank[cur] = depth; 
        int minimum_depth = depth;
        for(auto & next: graph[cur]){
            if (next.first == parent){
                continue;
            }
            int parent_depth = dfs(graph, critial, rank, depth+1, cur, next.first);
            if (parent_depth >depth) {
                critial[next.second] = 1;
            } 
            minimum_depth = min(minimum_depth, parent_depth);
        }
        return  rank[cur] = minimum_depth;
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int,int>>>graph(n);
        for(int i = 0; i<connections.size(); ++i){
            int e1 = connections[i][0], e2 = connections[i][1];
            graph[e1].push_back({e2, i});
            graph[e2].push_back({e1, i});
        }
        vector<int>rank(n, -1);
        vector<int>critial(connections.size(), 0);
        dfs(graph, critial, rank, 0, -1, 0);

        vector<vector<int>> res;
        for(int i = 0 ;i <critial.size();++i){
            if (critial[i]){
                res.push_back({connections[i][0], connections[i][1]});
            }
        }
        return res;
    }
};