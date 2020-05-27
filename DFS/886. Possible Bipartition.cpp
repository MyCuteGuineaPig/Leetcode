//DFS
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        if(dislikes.empty())
            return true;
        unordered_map<int,vector<int>>mp;
        for(auto d: dislikes){
            mp[d[0]].push_back(d[1]);
            mp[d[1]].push_back(d[0]);
        }
        vector<int>dp(N+1,-1);
        for(int i = 1; i<=N; ++i)
            if(dp[i] == -1 && !dfs(mp, dp, 1, i))
                return false;
        return true;
    }
    
    bool dfs(unordered_map<int,vector<int>>&mp, vector<int>&dp, int color, int point){
        if(dp[point]!=-1)
            return dp[point] == color;
        dp[point] = color;
        for(auto next: mp[point])
            if(!dfs(mp, dp, color^1, next))
                return false;
        return true;
    }   
};


//BFS
// Time complexity: O(|V| + |E|)
// Space complxity: O(|V|)
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        if(dislikes.empty())
            return true;
        unordered_map<int,vector<int>>mp;
        for(auto d: dislikes){
            mp[d[0]].push_back(d[1]);
            mp[d[1]].push_back(d[0]);
        }
        vector<int>dp(N+1,0);
        for(int i = 1; i<=N; ++i){
            queue<int>q;
            if(dp[i]==0)
                q.push(i);
            
            int color = 1;
            
            while(!q.empty()){
                int size = q.size();
                for(int j = 0; j<size; ++j){
                    int top = q.front(); q.pop();
                    dp[top] = color;
                    for(auto nxt: mp[top]){
                        if(dp[nxt]!= 0){
                            if(dp[nxt] != -color)
                                return false;
                        }else
                            q.push(nxt);
                    }
                }
                color *= -1;
            }
        }   
        return true;
    } 
};