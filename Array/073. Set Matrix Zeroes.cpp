/*
73. Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:

Input: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
Example 2:

Input: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]
Follow up:

A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?


*/

/*
如果matrix[i][j] == 0, 把matrix[i][0] 和matrix[0][j] 设为0

如果matrix[i][0] = 0, 再设为col0 = 0, 最后调整第一列的数


store states of each row in the first of that row, 
and store states of each column in the first of that column. 
Because the state of row0 and the state of column0 would occupy the same cell, 
I let it be the state of row0, and use another variable "col0" for column0. 
In the first phase, use matrix elements to set states in a top-down way. 
In the second phase, use states to set matrix elements in a bottom-up way.

用col0 是因为matrix[0][0] 不能同时代表 第0行都是0 和 第0列都是0， 
所以我们设 matrix[0][0] 表示第0行都是0， 第0列是不是0 用col0表示

*/


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int col0 = 1;
        for(int i = 0; i<matrix.size();i++){
            if(matrix[i][0] == 0) col0 = 0;
            for(int j = 1; j<matrix[0].size(); j++)
                if(matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;
        }

        for(int i = 1; i<matrix.size(); i++)
            for(int j = 1; j<matrix[0].size(); j++)
                if(matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
        
        if(matrix[0][0] == 0) for(int i = 0; i<matrix[0].size(); i++) matrix[0][i] = 0; //第一行
        if(col0 == 0) for(int i = 0; i<matrix.size(); i++) matrix[i][0] = 0; //第一列
        
    }
};


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int col0 = 1;
        for(int i = 0; i<matrix.size();i++){
            if(matrix[i][0] == 0) col0 = 0;
            for(int j = 1; j<matrix[0].size(); j++)
                if(matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;
        }

        for(int i = matrix.size()-1; i>=0; i--){ //从下往上，这样可以最后操作第一行, 第一行存着某列为0的数
            for(int j = 1; j<matrix[0].size(); j++)
                if(matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            if(col0 == 0) matrix[i][0] = 0;
        }
        
    }
};


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return;
        }

        bool has_zero = false;
        int zero_i = -1, zero_j = -1;

        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == 0) {
                    if (!has_zero) { //选取第一个为0的
                        zero_i = i;
                        zero_j = j;
                        has_zero = true;
                    }
                    matrix[zero_i][j] = 0;
                    matrix[i][zero_j] = 0;
                }
            }
        }

        if (has_zero) {
            for (int i = 0; i < matrix.size(); ++i) {
                if (i == zero_i) {
                    continue;
                }
                for (int j = 0; j < matrix[0].size(); ++j) {
                    if (j == zero_j) {
                        continue;
                    }
                    if (matrix[zero_i][j] == 0 || matrix[i][zero_j] == 0) {
                        matrix[i][j] = 0;
                    }
                }
            }
            for (int i = 0; i < matrix.size(); ++i) {
                matrix[i][zero_j] = 0;
            }
            for (int j = 0; j < matrix[0].size(); ++j) {
                matrix[zero_i][j] = 0;
            }
        }
    }
};
