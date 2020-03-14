class Solution {
public:
    vector<vector<int> > G;
    vector<bool> seen;
    int target;

    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if (n == 1) return 1.0;
        this->target = target;
        G = vector<vector<int> >(n + 1);
        for (auto e : edges) {
            G[e[0]].push_back(e[1]);
            G[e[1]].push_back(e[0]);
        }
        seen = vector<bool>(n + 1, false);

        return dfs(1, t);
    }

    double dfs(int i, int t) {
        if (i != 1 && G[i].size() == 1 || t == 0) {
            return i == target;
        }
        seen[i] = true;
        double res = 0;
        for (auto j : G[i]) {
            if (! seen[j]) {
                res += dfs(j, t - 1);
            }
        }
        return res / (G[i].size() - (i != 1));
    }
};