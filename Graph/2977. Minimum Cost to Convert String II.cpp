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


