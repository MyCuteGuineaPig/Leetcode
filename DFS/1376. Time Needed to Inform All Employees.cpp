class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        int res = 0;
        for (int i = 0; i < n; ++i)
            res = max(res, dfs(i, manager, informTime));
        return res;
    }

    int dfs(int i, vector<int>& manager, vector<int>& informTime) {
        if (manager[i] != -1) {
            informTime[i] += dfs(manager[i], manager, informTime);
            manager[i] = -1;
        }
        return informTime[i];
    }
};