class Solution {
public:
    int longestCycle(vector<int>& edges) {
        vector<pair<int,int>>path(edges.size(), {-1,-1});
        //first is the starting point, second is the distance from the starting point 
        int res = -1;
        for(int i = 0; i<edges.size(); ++i){
            for(int j = i, dist = 0; j != -1;j = edges[j]){
                if(path[j].first == -1){
                    path[j] = {i, ++dist};
                } else {
                    if (path[j].first == i)//find the cycle
                        res = max(res, dist-path[j].second + 1);
                    break;
                }
            }
        }
        return res;
        
    }
};

class Solution {
public:
    int DFS(vector<int>& edges, vector<pair<int,int>>& visited, int cur, int start, int dist){
        if (edges[cur] == -1)
            return -1;
        if (visited[cur].first != -1) {
            if (visited[cur].first  == start)
                return dist - visited[cur].second + 1;
            else 
                return -1;
        }  
        visited[cur] = {start, ++dist};
        return DFS(edges, visited, edges[cur], start, dist);
    }
    
    int longestCycle(vector<int>& edges) {
        vector<pair<int,int>> visited (edges.size(), {-1,-1});
        int res = -1;
        for(int i = 0; i<edges.size(); ++i){
            res = max(res, DFS(edges, visited, i, i, 0));
        }
        return res;
    }
};