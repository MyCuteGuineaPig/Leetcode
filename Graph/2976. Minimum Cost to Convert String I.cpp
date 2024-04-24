//normal DFS TLE


class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        if(source.size() != target.size()){
            return -1;
        }
        vector<vector<long long>>graph(26, vector<long long>(26, numeric_limits<int>::max()));
        for(int i = 0; i < original.size(); ++i){
            graph[original[i]-'a'][changed[i]-'a'] = min(graph[original[i]-'a'][changed[i]-'a'], (long long)cost[i]);
        }
        for(int k = 0; k < 26; ++k){
            for(int i = 0; i < 26; ++i){
                for(int j = 0; j < 26; ++j){
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
        long long res = 0; 
        for(int i = 0; i < source.size(); ++i){
            if(source[i] == target[i]) continue;
            if (graph[source[i]-'a'][target[i]-'a'] >= numeric_limits<int>::max()) return -1;
            res += graph[source[i]-'a'][target[i]-'a'];
            //cout<<" i "<<i<<" score "<<score<<" source[i] "<<source[i]<<" target[i] "<<target[i]<<" res "<<res<<endl;
        }
        return res;
    }
};




//Dijkstra
class Solution {
public:
    unordered_map<char,unordered_map<char, long long>>graph;
    unordered_map<char,unordered_map<char,long long>>dp;

    int find_shortest(char org, char dest){
        if(dp.count(org) && dp[org].count(dest)){
            return dp[org][dest];
        }
        priority_queue<pair<int, char>, vector<pair<int,char>>, greater<>>pq;
        pq.push({0, org});
        vector<int>dist(26, numeric_limits<int>::max());
        while(!pq.empty()){
            auto [far, cur] = pq.top(); pq.pop();
            if (cur == dest){
                return dp[org][dest] = far;
            }
            if (dist[cur-'a'] <= far ) continue;
            dist[cur-'a'] = far;
            for(auto & nxt: graph[cur]){
                if(dist[nxt.first-'a'] > nxt.second + far)
                    pq.push({nxt.second + far, nxt.first});
            }
        }
        return -1;
    }

    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        if(source.size() != target.size()){
            return -1;
        }
        for(int i = 0; i < original.size(); ++i){
            if(graph[original[i]].count(changed[i]) == 0){
                graph[original[i]][changed[i]] = (long long)cost[i];
            } else{
                graph[original[i]][changed[i]] = min(graph[original[i]][changed[i]], (long long)cost[i]);
            }
            
        }
        long long res = 0; 
        for(int i = 0; i < source.size(); ++i){
            if(source[i] == target[i]) continue;
            unordered_set<char>visited;
            int score = find_shortest(source[i], target[i]);
            if(score ==  -1 ){
                return -1;
            }
            res += score;
        }
        return res;
    }
};


typedef pair<int,int> pii;

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& O, vector<char>& C, vector<int>& cost) {
        vector<vector<pii>> adj(26);
        for (int i = 0; i < O.size(); i++) {
            adj[O[i]-'a'].push_back({C[i]-'a', cost[i]});
        }
        
        vector<vector<int>> memo(26, vector<int>(26, -1));
        
        function<int(int,int)> dijkstra = [&](int s, int e) {
            if (memo[s][e] != -1) return memo[s][e];
            
            int n = adj.size();
            vector<int> dist(n, INT_MAX);
            dist[s] = 0;

            priority_queue<pii, vector<pii>, greater<pii>> minq;
            minq.push({0, s});

            int u, v, w;
            while (!minq.empty()) {
                auto p = minq.top(); minq.pop();
                u = p.second;

                if (dist[u] < p.first)
                    continue;

                if (u == e)
                    return memo[s][e] = p.first;

                for (auto& node: adj[u]) {
                    v = node.first, w = node.second;
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        minq.push({dist[v], v});
                    }
                }
            }
            return memo[s][e] = (dist[e] == INT_MAX ? -2 : dist[e]);
        };
        
        long long res = 0;
        for (int i = 0; i < source.size(); i++) {
            if (source[i] != target[i]) {
                int c = dijkstra(source[i]-'a', target[i]-'a');
                if (c < 0) return -1;
                res += c;
            }
        }
        return res;
    }
};