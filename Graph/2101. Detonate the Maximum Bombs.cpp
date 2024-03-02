/*
不能用memoization 比如 

    int dfs(vector<vector<int>>&graph, vector<int>&visited,  int cur){
        if (visited[cur]) 
            return visited[cur];

        visited[cur] = 1;
        for(auto next: graph[cur]){
            int next_count = dfs(graph, visited, next);
            visited[cur] += next_count;
        }
        return visited[cur];
    }

比如 有Path 2->1, 更新 visited[1] = 1, visited[2] = 1
  还有Path 2 -> 3 -> 2 -> 1 
            3 -> 2的时候, 发现visited[2] > 0: visited[3] = 2 + 1 = 3,  visited[2] = 3 + 1 =  4, 有loop 了

不能用memoization 比如 
             1
            /  \ 
           /    3
          /    /   \   
        4   <-      5   
       /             \
      2               6

1 -> 4 - >2 更新dp[4] = 2, 到3 后, 3->4 把dp[4]再进去就duplicate了
               

*/

//DFS
class Solution {
public:
    int dfs(vector<vector<int>>&graph, vector<int>&visited,  int cur){
        visited[cur] = 1;
        for(auto next: graph[cur]){
            if (visited[next]) continue;
            int next_count = dfs(graph, visited, next);
            visited[cur] += next_count;
        }
        return visited[cur];
    }


    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>>graph(n);
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<n; ++j){
                if (i == j) continue;
                long x_diff = (bombs[j][0] -bombs[i][0]);
                long y_diff = (bombs[j][1] -bombs[i][1]);
                long r = bombs[i][2];
                if(x_diff*x_diff + y_diff*y_diff <= r*r ) {
                    graph[i].push_back(j);
                }
            }
        }
        int cur_max = 0;
       
        for(int i = 0; i<n; ++i){
            vector<int>visited(n);
            cur_max = max(cur_max, dfs(graph, visited, i));
        }
        return cur_max;
    }
};


//BFS
class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>>graph(n);
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<n; ++j){
                if (i == j) continue;
                long x_diff = (bombs[j][0] -bombs[i][0]);
                long y_diff = (bombs[j][1] -bombs[i][1]);
                long r = bombs[i][2];
                if(x_diff*x_diff + y_diff*y_diff <= r*r ) {
                    graph[i].push_back(j);
                }
            }
        }
        int cur_max = 0;    
        for(int i = 0; i < n && cur_max < n; ++i){
            queue<int>q; q.push(i);
            unordered_set<int>st = {i};
            while(q.size()){
                int qsize = q.size();
                for(int j = 0; j < qsize; ++j ){
                    int top = q.front(); q.pop();
                    for(auto &next: graph[top]){
                        if(st.insert(next).second){
                            q.push(next);
                        }
                    }
                }
            }
            cur_max = max(cur_max, (int)st.size());
        }
        return cur_max;
    }
};