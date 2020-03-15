class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        // Time Complexity: O(mn)
        // Space Complexity: O(m + n)
        int m(matrix.size()), n(matrix[0].size());
		// record min of each row and max of each column
        vector<int> mins(m, 100001), maxs(n);
        vector<int> lucky;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                mins[i] = min(mins[i], matrix[i][j]);
        for (int j = 0; j < n; ++j)
            for (int i = 0; i < m; ++i)
                maxs[j] = max(maxs[j], matrix[i][j]);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (maxs[j] == matrix[i][j] && mins[i] == matrix[i][j])
                    lucky.push_back(matrix[i][j]);
        return lucky;
    }
};



//set Interaction
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        // Time Complexity: O(mn)
        // Space Complexity: O(min(m, n)) <- slightly improved, not max(m, n)
        int m(matrix.size()), n(matrix[0].size());
        unordered_set<int> extrema;
        vector<int> lucky;
        if (m < n) {
            for (int i = 0; i < m; ++i) {
                int r(100001);
                for (int j = 0; j < n; ++j)
                    r = min(r, matrix[i][j]);
                extrema.insert(r);
            }
            for (int j = 0; j < n; ++j) {
                int c(0);
                for (int i = 0; i < m; ++i)
                    c = max(c, matrix[i][j]);
                if (extrema.count(c)) lucky.push_back(c);
            }
        } else {
            for (int j = 0; j < n; ++j) {
                int c(0);
                for (int i = 0; i < m; ++i)
                    c = max(c, matrix[i][j]);
                extrema.insert(c);
            }
            for (int i = 0; i < m; ++i) {
                int r(100001);
                for (int j = 0; j < n; ++j)
                    r = min(r, matrix[i][j]);
                if (extrema.count(r)) lucky.push_back(r);
            }
        }
        
        return lucky;
    }
};