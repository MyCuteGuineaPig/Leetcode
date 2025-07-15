class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, int k) {
        sort(edges.begin(), edges.end(), [&](vector<int>&a, vector<int>&b) {return a[2] > b[2];});
        vector<int>root(n); iota(root.begin(), root.end(), 0);
        auto find = [&](this auto&& find, int x) -> int{
            return root[x] == x ? x : root[x] = find(root[x]);
        };
        int cc = n;
        for(auto& e: edges){
            int r_a = find(e[0]);
            int r_b = find(e[1]);
            
            if(r_a != r_b) {
                cc -= 1;
                root[r_a] = root[r_b];
                if (cc < k) 
                    return e[2];
            }
        }
        return 0;
    }
};