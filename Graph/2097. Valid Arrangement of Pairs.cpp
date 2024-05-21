class Solution {
public:
    void dfs(unordered_map<int, stack<int>>&graph, vector<vector<int>>&res, int cur){
        auto& stk = graph[cur];
        while(!stk.empty()){
            int nxt = stk.top();
            stk.pop();
            dfs(graph, res, nxt);
            res.push_back({cur, nxt});
            //只能是在end  push_back, 
        }
    }

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int n = pairs.size();
        unordered_map<int,stack<int>>graph;
        unordered_map<int,int>in;
        unordered_map<int,int>out;
        for(auto &p: pairs){
            //cout<<p[0] <<" p[1] "<<p[1]<<endl;
            graph[p[0]].push(p[1]);
            ++out[p[0]];
            ++in[p[1]];
        }
        int start = -1;
        for(auto &p: pairs){
            int cur = p[0];
            if(out[cur] - in[cur] == 1){
                start = cur;
                break;
            }
        }
        vector<vector<int>>res;
        if (start == -1) {start = graph.begin()->first; }
        dfs(graph, res, start);
        //reverse(res.begin(), res.end());
        return res;
    }
};