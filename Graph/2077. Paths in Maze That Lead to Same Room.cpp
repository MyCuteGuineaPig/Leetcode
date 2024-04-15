class Solution {
public:
    int dfs(unordered_map<int,unordered_set<int>>&graph, int cur, int start, int count){
        //cout<<" int "<<cur<<" start "<<start<<"  count "<<count<<endl;
        if(count == 2){
            return graph[cur].count(start);
        }
        int res = 0;
        for(auto nxt: graph[cur]){
            if (nxt < cur) continue; //avoid double counting
            res += dfs(graph, nxt, start, count + 1);
        }
        return res;
    }

    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int,unordered_set<int>>graph;
        for(auto & e: corridors){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }

        int res = 0;
        for(int i = 1; i <= n; ++i){
            res += dfs(graph, i, i, 0);
        }
        return res;
    }
};


class Solution {
public:
    int dfs(unordered_map<int,unordered_set<int>>&graph, int cur, int start, int count){
        //cout<<" int "<<cur<<" start "<<start<<"  count "<<count<<endl;
        if(count == 2){
            return graph[start].count(cur);
        }
        int res = 0;
        for(auto nxt: graph[cur]){
            res += dfs(graph, nxt, start, count + 1);
        }
        return res;
    }

    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        unordered_map<int,unordered_set<int>>graph; 
        for(auto & e: corridors){
            graph[min(e[0], e[1])].insert(max(e[0], e[1])); //avoid double counting
        }

        int res = 0;
        for(int i = 1; i <= n; ++i){
            res += dfs(graph, i, i, 0);
        }
        return res;
    }
};



class Solution {
public:
    int numberOfPaths(int n, vector<vector<int>>& corridors) {
        vector<vector<int>>graph(n+1, vector<int>(n+1)); 
        for(auto & e: corridors){
            graph[min(e[0], e[1])][max(e[0], e[1])] = 1; //avoid double counting
        }

        int res = 0;
        for(int i = 1; i <n; ++i){
            for(int j = i + 1; j < n; ++j){
                for(int k = j + 1; graph[i][j] && k<=n; ++k){
                    res += graph[j][k] && graph[i][k];
                }
            }
        }
    

        return res;
    }
};