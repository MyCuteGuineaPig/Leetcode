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