class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<int>node(c);
        vector<int>status(c, 1);
        iota(node.begin(), node.end(), 0);
        auto find = [&](this auto && find, int i) {
            if (node[i] == i) return node[i];
            return node[i] = find(node[i]);
        };
        
        for(auto & conn : connections){
            int src_0 = find(conn[0]-1), src_1 = find(conn[1]-1);
            if (src_0 != src_1) 
                node[src_1] = src_0;
        }

        vector<priority_queue<int, vector<int>, greater<>>> heap(c);
        for(int i = 0 ; i < c; ++ i){
            int src = find(i);
            heap[src].push(i);
        }
        vector<int>res; 
        for(auto& q: queries) {
            if (q[0] == 2) {
                status[q[1]-1] = 0;
            }
            else if (status[q[1]-1]) {
                res.push_back(q[1]);
            }
            else {
                int src = find(q[1]-1);
                while (heap[src].size() && status[heap[src].top()] == 0) 
                {
                    heap[src].pop();
                }
                if (heap[src].size()) {
                    res.push_back(heap[src].top()+1);
                } else {
                    res.push_back(-1);
                }
            }
        }
        return res;
    }
};