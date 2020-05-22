class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int res = 0;
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix[0].size(); res += matrix[i][j++])
                if (matrix[i][j] && i && j)
                    matrix[i][j] += min({matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1]});
        return res;
    }
};

/**
 matrix[i][j] += matrix[i - 1][j - 1]; 不可以这么写的原因比如:
 下面的 matrix[2][2] = matrix[1][1] + 1 = 3, 但实际长度是2

             DP will be 
   1, 1, 0    1, 1, 0
   1, 1, 1    1, 2, 1
   0, 1, 1    0, 1, 0      

 */


class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        for (int i = 1; i < matrix.size(); ++i) {
            for (int j = 1; j < matrix[0].size(); ++j) {
                if (!matrix[i][j]) {
                    continue;
                }
                int l = min(matrix[i - 1][j], matrix[i][j - 1]);
                matrix[i][j] = matrix[i - l][j - l] ? l + 1 : l;
            }
        }
        int result = 0;
        for (const auto& row : matrix) {
            for (const auto& x : row) {
                result += x;
            }
        }
        return result;
    }
};