class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        sort(sources.begin(), sources.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] > b[2];
        });
        vector<vector<int>> A(n, vector<int>(m, 0));
        for (const auto& s : sources) {
            A[s[0]][s[1]] = s[2];
        }
        int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int k = 0; k < sources.size(); ++k) {
            int i = sources[k][0], j = sources[k][1], v = sources[k][2];
            for (int d = 0; d < 4; ++d) {
                int x = i + dx[d], y = j + dy[d];
                if (x >= 0 && x < n && y >= 0 && y < m && A[x][y] == 0) {
                    A[x][y] = v;
                    sources.push_back({x, y, v});
                }
            }
        }
        return A;
    }
};