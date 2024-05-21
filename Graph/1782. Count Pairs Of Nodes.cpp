class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int>cnt(n+1);
        vector<int>res(queries.size());
        vector<int>sorted_cnt(n+1);
        unordered_map<int, unordered_map<int,int>>counter;
        for(int i = 0; i < edges.size(); ++i){
            cnt[edges[i][0]] += 1; cnt[edges[i][1]] += 1; 
            sorted_cnt[edges[i][0]] += 1; sorted_cnt[edges[i][1]] += 1; 
            int s = min(edges[i][0], edges[i][1]);
            int e = max(edges[i][0], edges[i][1]);
            counter[s][e] += 1; 
        }
        sort(sorted_cnt.begin(), sorted_cnt.end());
        for(int i = 0; i < queries.size(); ++i){
            int l = 1, r = n;
            while(l < r){
                if (sorted_cnt[l] + sorted_cnt[r] > queries[i]){
                    res[i] += (r--) - l;
                } else {
                    ++l;
                }
            }
            for(auto &it1: counter){
                for(auto &it2: it1.second){
                    int s = it1.first, e = it2.first;
                    if(cnt[s] + cnt[e] > queries[i] && cnt[s] + cnt[e] - it2.second <= queries[i]  ){
                        --res[i];
                    }
                }
            }
        }
        return res;
    }
};