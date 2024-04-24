class Solution {
public:
    void backTrack(int cur, unordered_map<int, unordered_set<int>>& path,  vector<unordered_set<int>>&src){
        if(cur == 0){
            return;
        }
        for(auto &prev: src[cur]){
            path[prev].insert(cur);
            backTrack(prev, path, src);
        }
    }


    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_map<int,int>>graph;
        auto cmp = [](vector<int>& a, vector<int>& b){
            return a[0] > b[0];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)>pq(cmp);
        for(auto & e: edges){
            graph[e[0]][e[1]] = e[2];
            graph[e[1]][e[0]] = e[2];
        }
        pq.push({0, 0,-1});
        vector<unordered_set<int>>src(n);
        vector<int>dist(n, numeric_limits<int>::max()); 
        while(pq.size()){
            int far = pq.top()[0];
            int point = pq.top()[1];
            int prev = pq.top()[2];
            pq.pop();
            if (dist[point] == far){
                src[point].insert(prev);
            }
            else if (dist[point] > far){
                dist[point] = far;
                src[point].insert(prev);
                for(auto &nxt: graph[point]){
                    //
                    int nxt_far = far + nxt.second;
                    if (dist[nxt.first] >= nxt_far){
                        pq.push({nxt_far, nxt.first, point});
                    }
                }
            }
        }
        unordered_map<int, unordered_set<int>> path;
        backTrack(n-1, path, src);
        vector<bool>res;
        for(auto e: edges){
            if(path.count(e[0]) && path[e[0]].count(e[1]) || path.count(e[1]) && path[e[1]].count(e[0]))
                res.push_back(true);
            else
                res.push_back(false);
        }
        return res;
    }
};



class Solution {
public:

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        unordered_map<int, unordered_map<int,pair<int,int>>>graph;
        auto cmp = [](vector<int>& a, vector<int>& b){
            return a[0] > b[0];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)>pq(cmp);
        for(int i = 0; i < edges.size(); ++i){
            vector<int>& e = edges[i];
            graph[e[0]][e[1]] = {e[2], i};
            graph[e[1]][e[0]] = {e[2], i};
        }
        pq.push({0, 0});
        vector<int>dist(n, numeric_limits<int>::max()); 
        dist[0] = 0;
        while(pq.size()){
            int far = pq.top()[0];
            int point = pq.top()[1];
            pq.pop();
            if (dist[point] == far){
                for(auto &nxt: graph[point]){
                    int nxt_far = far + nxt.second.first;
                    if (dist[nxt.first] > nxt_far){
                        dist[nxt.first] = nxt_far;
                        pq.push({nxt_far, nxt.first});
                    }
                }
            }
        }
        pq.push({dist[n-1], n-1});
        vector<bool>res(edges.size(), false);
        while(!pq.empty()){
            int far = pq.top()[0];
            int point = pq.top()[1];
            pq.pop();
            for(auto &prev: graph[point]){
                int prev_far = far - prev.second.first;
                if(dist[prev.first] == prev_far){
                    int index = prev.second.second;
                    res[index] = true;
                    pq.push({dist[prev.first], prev.first});
                }
            }
        }
        return res;
    }
};