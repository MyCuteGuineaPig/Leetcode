//Dijkstra's Algorithm
class Graph {
public:
    unordered_map<int, unordered_map<int,int>>graph;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        for(auto edge:edges){
            graph[edge[0]][edge[1]] = edge[2];
        }
    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]][edge[1]] = edge[2];
    }
    
    int shortestPath(int node1, int node2) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>pq;
        pq.push({0, node1});
        vector<int>dist(n, numeric_limits<int>::max());
        dist[node1] = 0;
        while(!pq.empty()){
            int cur_dist = pq.top()[0]; 
            int cur = pq.top()[1];
            pq.pop();
            if (cur == node2) return cur_dist;
            for(auto nxt: graph[cur]){
                if(dist[nxt.first] > cur_dist + nxt.second){
                    dist[nxt.first] = cur_dist + nxt.second;
                    pq.push({cur_dist + nxt.second, nxt.first});
                }
            } 
        }
        return -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */


//Approach 2: Floyd–Warshall algorithm
class Graph {
public:
    vector<vector<int>>adjMatrix;
    int n;
    Graph(int n, vector<vector<int>>& edges) {
        adjMatrix.resize(n, vector<int>(n, 1e9));
        this->n = n;
        for(auto & edge: edges){
            adjMatrix[edge[0]][edge[1]] = edge[2];
        }
        for(int i = 0; i < n; ++i)
            adjMatrix[i][i] = 0;  //<--- this is important
        for(int k = 0; k <n; ++k){
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                }
            }
        }
    }
    
    void addEdge(vector<int> edge) {
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][edge[0]] + adjMatrix[edge[1]][j] + edge[2]);
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        if (adjMatrix[node1][node2] >= 1e9){
            return -1;
        }

        return adjMatrix[node1][node2];
    }
};





class Graph {
    int n;
    vector<vector<long>> distances; // <-- use long to avoid integer overflow 
public:
    
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        distances.resize(n, vector<long>(n, numeric_limits<int>::max()));
        for(auto edge: edges)
            distances[edge[0]][edge[1]] = edge[2];
        for(int i = 0; i < n; ++i) 
            distances[i][i] = 0;
        
        for(int k = 0; k < n; ++k) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if (distances[i][k]!= numeric_limits<int>::max() && distances[k][j]!= numeric_limits<int>::max()) {
                        distances[i][j] = min(distances[i][j],  distances[i][k] +  distances[k][j]);
                    }
                }
            }
        }
    }
    
    void addEdge(vector<int> edge) {
        //distances[edge[0]][edge[1]] = edge[2]; <-- don't add this because there might be a shorter path

        distances[edge[0]][edge[1]] = min(distances[edge[0]][edge[1]], (long)edge[2]);
        
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j) {
                if (distances[i][edge[0]]!=  numeric_limits<int>::max() && distances[edge[1]][j]!=  numeric_limits<int>::max()){
                 distances[i][j] = min(distances[i][j],  distances[i][edge[0]] +  distances[edge[1]][j] + edge[2]);
                }
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        return distances[node1][node2] == numeric_limits<int>::max()? -1: distances[node1][node2];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */