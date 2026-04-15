class Solution {
public:
    int count(unordered_map<int, unordered_map<int,int>>&graph, vector<long>&dist, vector<int>&dp, int cur){
        if(cur == 1){
            return 1;
        }
        if(dp[cur] >= 0) return dp[cur];
        dp[cur] = 0;
        static int mod = 1e9+7;
        for(auto & nxt: graph[cur]){
            if(dist[cur] < dist[nxt.first]){
                dp[cur] = (dp[cur] + count(graph, dist, dp, nxt.first)) % mod;
            }
        }
        return dp[cur];
    }

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_map<int,int>>graph;
        for(auto & edge: edges){
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
        vector<long>dist(n+1, 1e10);
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>pq;
        pq.push({0,n});
        dist[n] = 0;
        while(!pq.empty()){
            int cur_dist = pq.top()[0];
            int cur = pq.top()[1]; pq.pop();
            for(auto &nxt: graph[cur]){
                if(dist[nxt.first] > nxt.second + cur_dist){
                    dist[nxt.first] = nxt.second + cur_dist;
                    pq.push({nxt.second + cur_dist,nxt.first});
                }
            }
        }
        //for(int i = 1; i<=n; ++i)
        //    cout<<i<<" dist[i]=" <<dist[i]<<endl;
        vector<int>dp(n+1, -1);
        return count(graph, dist, dp, n);
    }
};

/*
1 dist[i]=300000
2 dist[i]=200000
3 dist[i]=100000
4 dist[i]=0
*/



class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<int>distances(n+1, numeric_limits<int>::max());
        unordered_map<int, unordered_map<int, int>> graph;
        for(auto& edges: edges){
            graph[edges[0]][edges[1]] = edges[2];
            graph[edges[1]][edges[0]] = edges[2];
        }
        distances[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, n});
        while (!pq.empty()) {
            auto [cur_dist, node] = pq.top(); pq.pop();
            if (distances[node] < cur_dist) continue;
            for(auto& [neighbor, dist] : graph[node]) {
                int next_dist = cur_dist + dist;
                if (distances[neighbor] > next_dist) {
                    distances[neighbor] = next_dist;
                    pq.push({next_dist, neighbor});
                }
            }
        }
        long mod = 1e9 + 7;

        vector<int>dp(n+1, -1);
        auto helper = [&](this auto&& helper, int cur) { 
            // 即使是undirected graph 不会有循环，
            // 因为有distances[neighbor] < distances[cur]
            if (cur == n) {
                return 1;
            } 
            if (dp[cur] >= 0) return dp[cur];
            dp[cur] = 0;
            for(auto& [neighbor, dist] : graph[cur]) {
                if(distances[neighbor] < distances[cur]) {
                    dp[cur] = (dp[cur] + helper(neighbor)) % mod;
                }
            }
            return dp[cur];
        };
         
        return helper(1);
    }
};



//iterative
class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<int>distances(n+1, numeric_limits<int>::max());
        unordered_map<int, unordered_map<int, int>> graph;
        for(auto& edges: edges){
            graph[edges[0]][edges[1]] = edges[2];
            graph[edges[1]][edges[0]] = edges[2];
        }
        distances[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, n});
        while (!pq.empty()) {
            auto [cur_dist, node] = pq.top(); pq.pop();
            if (distances[node] < cur_dist) continue;
            for(auto& [neighbor, dist] : graph[node]) {
                int next_dist = cur_dist + dist;
                if (distances[neighbor] > next_dist) {
                    distances[neighbor] = next_dist;
                    pq.push({next_dist, neighbor});
                }
            }
        }
        long mod = 1e9 + 7;

        vector<long>dp(n+1);
        dp[n] = 1;
        for(int i = 0; i <= n; i++)
            pq.push({distances[i], i});

        while(!pq.empty()) {
            auto [_, node] = pq.top(); pq.pop();
            for(auto& [neighbor, _] : graph[node]) {
                if (distances[neighbor] > distances[node]) {
                    dp[neighbor] = (dp[neighbor]+ dp[node]) % mod;
                }
            }
        }
         
        return dp[1];
    }
};