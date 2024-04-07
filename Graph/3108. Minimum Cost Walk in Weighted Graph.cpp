class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int>parent(n);
        iota(parent.begin(), parent.end(), 0);
        vector<int>cost(n,-1);
        function<int(int)> find = [&](int i) -> int {
            return parent[i] == i ? i: parent[i] = find(parent[i]);
        };
        for(auto & e: edges){
            cout<<e[0]<<" e[1] "<<e[1]<<endl;
            int p1 = find(e[0]), p2=find(e[1]);
            if (p1 != p2){
                cost[p1] &= cost[p2];
                parent[p2] = p1;
            }
            cost[p1] &= e[2];
        }
        vector<int>res;
        for(auto q: query){
            if(q[0] == q[1]){
                res.push_back(0);
            } else{
                int p1 = find(q[0]);
                int p2 = find(q[1]);
                if (p1 != p2) res.push_back(-1);
                else res.push_back(cost[p1]);
            }
        }
        return res;
    }
};