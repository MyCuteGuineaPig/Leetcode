class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        if(graph.size()==1) 
            return 0;
        queue<pair<int,int>>q; 
        
        for(int i = 0; i<graph.size();++i)
            q.push({i,1<<i});
            
        int step = 0, target = (1 << graph.size())-1;
        
        while(!q.empty()){
            ++step;
            unordered_map<int,unordered_set<int>>visited;
            for(int z = q.size(); z>0; --z){
                
                pair<int,int>top = q.front(); q.pop();
                for(auto nxt: graph[top.first]){
                    
                    int path = top.second | (1<<nxt);
                    if(visited[nxt].count(path) )
                        continue;
                    visited[nxt].insert(path);
                    if(path == target){
                        return step;
                    }

                    q.push({nxt,path});
                }
            }
        }
        return -1;
    }
};




/**
 * 
 Method 2:

int bitMask: mask of all the nodes we visited so far: 0 -> not visited, 1 -> visited (Originally this was Set<Integer>of
     all nodes we visited so far, but since the Solution TLE and N <= 12, it turns out we can use a bitMask 
     and 32 bits total in an Integer can cover all the possibilities. This is a small speed up optimization.)
int curr: current node we are on
int cost: the total cost in the path.

Each path taken will have a unique combination of these 3 variables.
 */


struct Tuple {
    int bitMask;
    int curr;
    int cost;

    Tuple(int bit, int n, int c) {
        bitMask = bit;
        curr = n;
        cost = c;
    }

    bool equals(const Tuple& p) const {
        return bitMask == p.bitMask && curr == p.curr && cost == p.cost;
    }

    int hashCode() const {
        return 1331 * bitMask + 7193 * curr + 727 * cost;
    }
};



struct Hash {
    size_t operator() (const Tuple &p) const {
        return p.hashCode();
    }
};

static bool operator==(const Tuple& lhs, const Tuple& rhs) {
    return lhs.equals(rhs);
}

class Solution {
public:
     int shortestPathLength(vector<vector<int>>& graph) {

        int N = graph.size();

        queue<Tuple> q;
        unordered_set<Tuple, Hash> visited;

        for (int i = 0; i < N; i++) {
            int tmp = (1 << i);
            visited.emplace(Tuple(tmp, i, 0));
            q.emplace(Tuple(tmp, i, 1));
        }

        while (!q.empty()) {
            Tuple curr = q.front();
            q.pop();

            if (curr.bitMask == (1 << N) - 1) {
                return curr.cost - 1;
            }
            else {
                auto& neighbors = graph[curr.curr];

                for (int v : neighbors) {
                    int bitMask = curr.bitMask;
                    bitMask |= (1 << v);

                    Tuple t(bitMask, v, 0);
                    if (!visited.count(t)) {
                        q.emplace(Tuple(bitMask, v, curr.cost + 1));
                        visited.emplace(t);
                    }
                }
            }
        }
        return -1;
    }
};