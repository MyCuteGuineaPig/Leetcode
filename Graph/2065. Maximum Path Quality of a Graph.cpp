/*

We have at most 10 steps, and it is also given that each node have at most degree 4, 
so in total we can make no more than 4^10 states. That is why we will not get TLE.
*/

class Solution {
public:
    void dfs(unordered_map<int,unordered_map<int, int>>& graph, vector<int>& values, int cur, int gain, int time_remain, int& max_gain){
        gain += values[cur];
        if(cur == 0){
            max_gain = max(max_gain, gain);
        }
        int tmp = values[cur];
        values[cur] = 0; ///setting value of the visited node to 0 so that we dont add it back while returning to 0
        for(auto &nxt: graph[cur]){
            if (nxt.second <= time_remain){
                dfs(graph,values, nxt.first, gain, time_remain - nxt.second , max_gain);
            }
        }
        values[cur] = tmp;
    }


    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        unordered_map<int,unordered_map<int, int>> graph;
        for(auto e: edges){
            graph[e[0]][e[1]] = e[2];
            graph[e[1]][e[0]] = e[2];
        }
        int max_gain = 0;
        dfs(graph, values, 0, 0, maxTime, max_gain);
        return max_gain;
    }
};


class Solution {
public:
    void dfs(unordered_map<int,unordered_map<int, int>>& graph, vector<int>& values, unordered_set<int>&counted, int cur, int gain, int cost, int& max_gain){
        //cout<<" []in] "<<cur<<" gain "<<gain<<" cost "<<cost<<endl;
        if(cur == 0){
            max_gain = max(max_gain, gain);
        }
        for(auto &nxt: graph[cur]){
            if (nxt.second <= cost){
                int new_gain = counted.count(nxt.first) ? gain: gain+values[nxt.first];
                //cout<<" cur "<<cur<<" nxt "<<nxt.first<<" new_gain "<<new_gain<<endl;
                
                bool success = counted.insert(nxt.first).second;
                dfs(graph,values, counted, nxt.first, new_gain, cost - nxt.second , max_gain);
                if (success)
                    counted.erase(nxt.first);
            }
        }
    }


    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        unordered_map<int,unordered_map<int, int>> graph;
        for(auto e: edges){
            graph[e[0]][e[1]] = e[2];
            graph[e[1]][e[0]] = e[2];
        }
        int max_gain = 0;
        unordered_set<int>counted; counted.insert(0);
        dfs(graph, values, counted, 0, values[0], maxTime, max_gain);
        return max_gain;
    }
};




class Solution {
public:
    int time; //saving the max time allowed
    int ans = 0; //saving the final ans
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        time = maxTime;
        int n = values.size();
        vector<pair<int,int>>adj[n];   //adjacency list
        for(auto &i : edges){
            adj[i[0]].push_back({i[1],i[2]});
            adj[i[1]].push_back({i[0],i[2]});
        }
        dfs(0,0,0,values,adj);
        return ans;
    }
    void dfs(int node, int currTime, int currVal , vector<int>& val , vector<pair<int,int>>adj[]){
        if(currTime > time) return; //if time exceeds max time this is not a valid path
        currVal += val[node]; //adding node's value as we reach that node
        if(node == 0){
            ans = max(ans,currVal); // if we reach 0 again comparing values we goth from path and saving max here
        }
        int temp = val[node];  //saving the val of node, why? check next line
        val[node] = 0; //setting value of the counted node to 0 so that we dont add it back while returning to 0
        for(auto &edge : adj[node]){
            dfs(edge.first,currTime+edge.second,currVal,val,adj);
        }
        val[node] = temp; //backtracking, giving node it's value back
    }
};