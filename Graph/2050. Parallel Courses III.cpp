class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>>graph(n+1);
        vector<int>degree(n+1);
        for(int i = 0; i < relations.size(); ++i){
            graph[relations[i][0]].push_back(relations[i][1]);
            ++degree[relations[i][1]];
        }

        vector<int>cnt(n+1);
        queue<int> q;
        for(int i = 1; i <= n; ++i){
            if(degree[i] == 0){
                q.push(i);
                cnt[i] = time[i-1];
            }
        }

        while(!q.empty()){
            int size = q.size();
            for(int a = 0; a < size; ++a){
                auto course  = q.front(); q.pop();   
                for(auto nxt: graph[course]){
                    cnt[nxt]  = max(cnt[nxt],cnt[course] + time[nxt-1]);
                    if (--degree[nxt] == 0){
                        q.push(nxt);
                    }
                }
            }
        }
        return *max_element(cnt.begin(), cnt.end());
    }
};