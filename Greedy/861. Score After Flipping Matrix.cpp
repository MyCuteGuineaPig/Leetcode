//🔍 先保证第一列全是1, 然后决定toggle每一列从再最大化每一列

/*
思路: 一列一列的看
为了最大化和，我们首先要先把第一列所有数变成1，
    - 把A[i][0] = 0的数变成 1, toggle i行 where A[i][0] = 0
    - A[i][0] = 1 那行不变
    A[i][0] 每个1 值 乘以 1<<(N-1) 

接下来看A[i][j], 因为A[i][0] 已经是1 了，
    假设A[i][0] 在没变化之前
        - A[i][0] = 0, A[i][j] = 1, toggle 第i行后 现在A[i][[j] = 0, count += 0
        - A[i][0] = 1, A[i][j] 不发生变化,   

所以在A[i][0] 变化之后，j列1的个数 = A[i][j] == A[i][0]， 假设有k个，
    我们可以对比 k大还是row行数 - k; 如果是row - k大，我们可以toggle j列

*/


class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int R = A.size(), C = A[0].size(), res = 0;
        for(int j = 0; j<C; j++){
            int col = 0;
            for(int i = 0; i<R; i++) col += A[i][j] == A[i][0]; 
            res += max(col, R - col)*(1<<(C -  1 - j));
        }
        return res;
    }
};

class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int R = A.size();
        int C = A[0].size();
        int result = 0;
        for (int c = 0; c < C; ++c) {
            int col = 0;
            for (int r = 0; r < R; ++r) {
                col += A[r][c] ^ A[r][0]; //算0的个数
            }
            result += max(col, R - col) * (1 << (C - 1 - c));
        }
        return result;
    }
};

class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int M = A.size(), N = A[0].size(), res = (1 << (N - 1)) * M;
        for (int j = 1; j < N; j++) {
            int cur = 0;
            for (int i = 0; i < M; i++) cur += A[i][j] == A[i][0];
            res += max(cur, M - cur) * (1 << (N - j - 1));
        }
        return res;
    }
};