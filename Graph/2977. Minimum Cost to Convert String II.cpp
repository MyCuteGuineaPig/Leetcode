class Solution {
public:
    unordered_map<int, unordered_set<string>>size_map;
    unordered_map<string, unordered_map<string, long long>> dist;
    unordered_map<int, long long> dp;

    long long dfs(int index, const string& source, const string& target){
        if(index >= source.size())
            return 0;
        if(dp.count(index))
            return dp[index];
        dp[index] = 1e15;
        if(source[index] == target[index])
            dp[index] = dfs(index + 1, source, target);
        for(auto &[size, _]: size_map){
            if(index + size <= source.size()){
                string tmp_source = source.substr(index, size);
                string tmp_target = target.substr(index, size);
                if(dist.count(tmp_source) && dist[tmp_source].count(tmp_target)){
                    dp[index] = min(dp[index], dist[tmp_source][tmp_target] + dfs(index + size, source, target));
                }
            }
        }
        return dp[index];
    }

    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        for(int i = 0; i < original.size(); ++i){
            size_map[original[i].size()].insert(original[i]);
            if (dist[original[i]].count(changed[i]) == 0){
                dist[original[i]][changed[i]] = cost[i];
            } else 
                dist[original[i]][changed[i]] = min( dist[original[i]][changed[i]],(long long)cost[i]);
        }

        for(auto& [size, org_set]: size_map){
            for(auto & mid: org_set){
                for(auto & org: org_set){//注意loop 顺序 不可以先org 再mid 只能先mid 再org
                    if(dist[org].count(mid)){
                        for(auto& [des, c]: dist[mid]){
                            if(dist[org].count(des) == 0)
                                dist[org][des] = 1e15;
                            dist[org][des] = min(dist[org][des], dist[org][mid] + dist[mid][des]);
                        }
                    }
                }
            }
        }
        
        
        long long res = dfs(0, source, target);
        return res >= 1e15 ? -1: res;
    }
};







class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        unordered_map<string, unordered_map<string, long long>> dist_mp;
        unordered_map<int, unordered_set<string>>size_mp;
        for(int i = 0; i < original.size(); ++i){
            size_mp[original[i].size()].insert(original[i]);
            if(dist_mp[original[i]].count(changed[i])==0){
                dist_mp[original[i]][changed[i]] = cost[i];
            } else {
                dist_mp[original[i]][changed[i]] = min(dist_mp[original[i]][changed[i]], (long long)cost[i]);
            }
        }
        for(auto &[size, org_set]: size_mp){
            for(auto & mid: org_set){
                for(auto & org: org_set){
                    if(dist_mp[org].count(mid)){
                        for(auto &[dest, c]: dist_mp[mid]){
                            if(dist_mp[org].count(dest) == 0)
                                dist_mp[org][dest] = 1e15;
                            dist_mp[org][dest] = min(dist_mp[org][dest], c + dist_mp[org][mid]);
                        }
                    }
                }
            }
        }

        vector<long long>dp(source.size()+1, 1e15);
        dp[0] = 0;
        for(int i = 0; i < source.size(); ++i){
            if(dp[i] == 1e15) continue;
            if(source[i] == target[i])
                dp[i+1] = min(dp[i+1], dp[i]);
            for(auto [size, _]: size_mp){
                if (i + size > source.size()) continue;
                string src_tmp = source.substr(i,size);
                string tgt_tmp = target.substr(i,size);
                if(dist_mp.count(src_tmp) && dist_mp[src_tmp].count(tgt_tmp)){
                    dp[i + size] = min(dp[i+size], dp[i] + dist_mp[src_tmp][tgt_tmp]);
                }
            }
        }
        return dp.back() >= 1e15 ? -1: dp.back();

    }
};



class Solution {
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
         unordered_map<string, int> index;
        for (const string& o : original) {
            if (!index.count(o)) {
                index[o] = index.size();
            }
        }
        for (const string& c : changed) {
            if (!index.count(c)) {
                index[c] = index.size();
            }
        }

        int n = index.size();
        vector<vector<long>> dis(n, vector<long>(n, LONG_MAX));

        for (int i = 0; i < cost.size(); ++i) {
            dis[index[original[i]]][index[changed[i]]] = min(dis[index[original[i]]][index[changed[i]]], (long)cost[i]);
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (dis[i][k] < LONG_MAX) {
                    for (int j = 0; j < n; ++j) {
                        if (dis[k][j] < LONG_MAX) {
                            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                        }
                    }
                }
            }
        }

        unordered_set<int> substrLengths;
        for (const string& o : original) {
            substrLengths.insert(o.length());
        }

        vector<long> dp(target.length() + 1, LONG_MAX);
        dp[0] = 0;

        for (int i = 0; i < target.length(); ++i) {
            if (dp[i] == LONG_MAX) {
                continue;
            }

            if (target[i] == source[i]) {
                dp[i + 1] = min(dp[i + 1], dp[i]);
            }

            for (int t : substrLengths) {
                if (i + t >= dp.size()) {
                    continue;
                }

                string subSource = source.substr(i, t);
                string subTarget = target.substr(i, t);

                int c1 = index.count(subSource) ? index[subSource] : -1;
                int c2 = index.count(subTarget) ? index[subTarget] : -1;

                if (c1 >= 0 && c2 >= 0 && dis[c1][c2] < LONG_MAX) {
                    dp[i + t] = min(dp[i + t], dp[i] + dis[c1][c2]);
                }
            }
        }

        return dp[dp.size() - 1] == LONG_MAX ? -1L : dp[dp.size() - 1];
    }
};