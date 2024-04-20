class Solution {
public:
    int dfs(unordered_map<int, vector<pair<int,int>>>& rows, unordered_map<int, vector<pair<int,int>>>&cols, int x, int y, unordered_set<string>&visited){
        int cnt = 1;
        string tmp = to_string(x) + "#" + to_string(y);
        visited.insert(tmp);
        for(auto &row_pair: rows[x]){
            int i = row_pair.first, j = row_pair.second;
            auto new_key = to_string(i) + "#" + to_string(j);
            if(visited.count(new_key)) continue;
            cnt += dfs(rows, cols, i, j, visited);
        }
        for(auto &col_pair: cols[y]){
            int i = col_pair.first, j = col_pair.second;
            auto new_key = to_string(i) + "#" + to_string(j);
            if(visited.count(new_key)) continue;
            cnt += dfs(rows, cols, i, j, visited);
        }
        return cnt;
    }

    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, vector<pair<int,int>>> rows;
        unordered_map<int, vector<pair<int,int>>> cols;
        unordered_set<string>visited;
        for(auto & s: stones){
            rows[s[0]].push_back({s[0], s[1]});
            cols[s[1]].push_back({s[0], s[1]});
        }

        int res = 0;
        for(auto &s: stones){
            string tmp = to_string(s[0]) + "#" + to_string(s[1]);
            if(visited.count(tmp)) continue;
            res += dfs(rows, cols, s[0], s[1],visited) -1;
        }
        return res;
    }
};


class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int,int>p;
        int island = 0; 
        for(auto &e: stones)
            uni(e[0], 100000 + e[1], p, island);
        return stones.size() - island;
    }

    int find(unordered_map<int, int>&p, int x, int& island){
        if(!p.count(x)) p[x] = x, ++island;
        return x == p[x]? x :  p[x] = find(p, p[x], island);
    }

    void uni(int x, int y, unordered_map<int, int>&p,  int& island){
        x = find(p, x, island);
        y = find(p, y, island);
        if ( x!= y) p[x] = y, island--;
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        for (int i = 0; i < stones.size(); ++i)
            uni(stones[i][0], ~stones[i][1]);
        return stones.size() - islands;
    }

    unordered_map<int, int> f;
    int islands = 0;

    int find(int x) {
        if (!f.count(x)) f[x] = x, islands++;
        if (x != f[x]) f[x] = find(f[x]);
        return f[x];
    }

    void uni(int x, int y) {
        x = find(x), y = find(y);
        if (x != y) f[x] = y, islands--;
    }
};



class Solution {
public:
    // Constant to map y-coordinates of stones
    const int K = 10001;
    void dfs(vector<vector<int>>& stones, vector<int> adj[], vector<int>& visited, int src) {
        // Mark the stone as visited
        visited[src] = 1;
        
        // Iterate over the adjacent, and iterate over it if not visited yet
        for (int adjacent : adj[src]) {
            if (visited[adjacent] == 0) {
                dfs(stones, adj, visited, adjacent);
            }
        }
    }
    
    int removeStones(vector<vector<int>>& stones) {
        // Adjacency list to store edges
        vector<int> adj[2 * K + 1];
        for (int i = 0; i < stones.size(); i++) {
            int x = stones[i][0];
            int y = stones[i][1] + K;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        
        // Array to mark visited stones
        vector<int> visited(2 * K + 1, 0);
        // Counter for connected components
        int componentCount = 0;
        for (int i = 0; i < 2 * K + 1; i++) {
            if (visited[i] == 0 && adj[i].size() > 0) {
                // If the stone is not visited yet,
                // Start the DFS and increment the counter
                componentCount++;
                dfs(stones, adj, visited, i);
            }
        }
        
        // Return the maximum stone that can be removed
        return stones.size() - componentCount;
    }
};



class Solution {
public:
    const int K = 10001;
    // Returns the representative of vertex x
    int find(vector<int>& rep, int x) {
        if (x == rep[x]) {
            return x;
        }
        return rep[x] = find(rep, rep[x]);
    }
    // Combine the stone x and y, and returns 1 if they were not connected
    int performUnion(vector<int>& rep, vector<int>& size, int x, int y) {
        x = find(rep, x);
        y = find(rep, y);
        
        if (x == y) {
            return 0;
        }
        
        if (size[x] > size[y]) {
            rep[y] = x;
            size[x] += size[y];
        } else {
            rep[x] = y;
            size[y] += size[x];
        }
        
        return 1;
    }
    
    int removeStones(vector<vector<int>>& stones) {
        vector<int> rep(2 * K + 1);
        vector<int> size(2 * K + 1);
        // Initialize rep to itself and size as 1
        for (int i = 0; i < 2 * K + 1; i++) {
            rep[i] = i;
            size[i] = 1;
        }
        
        int componentCount = 0;
        unordered_map<int, int> marked;
        for (vector<int> stone : stones) {
            if (marked.find(stone[0]) == marked.end()) {
                componentCount++;
            }
            
            if (marked.find(stone[1] + K) == marked.end()) {
                componentCount++;
            }
            
            marked[stone[0]] = 1;
            marked[stone[1] + K] = 1;
        }
        
        for (int i = 0; i < stones.size(); i++) {
            int x = stones[i][0];
            int y = stones[i][1] + K;
            // Decrement the componenets if union invloved merging
            componentCount -= performUnion(rep, size, x, y);
        }
        
        // Return the maximum stone that can be removed
        return stones.size() - componentCount;
    }
};