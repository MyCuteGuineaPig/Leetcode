/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
Example:

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.



*/

/*
sorted matrix题目的关键是从第一行最后一个开始，如果当前数比想要的大, --col, 如果当前数比想要的小，++row

column 只能减小，row只能增加, 一行一列的eliminate
如果当前数比想要的大, 不会在现在的col（因为现在col 往下的数都比 [row][col] 大）
如果当前数比想要的小, 不会在现在的row（因为现在row 往左的数都比 [row][col] 小）

比如 搜寻18 
  [1,   4,  7, 11, 15],    不会在第一行左面出现 15<18         不会在最后一列往下 19 > 18    不会在第二行往左出现 12 < 18
  [2,   5,  8, 12, 19],         [2,   5,  8, 12, 19],         [2,   5,  8, 12】        
  [3,   6,  9, 16, 22],  = 》   [3,   6,  9, 16, 22]    =》    [3,   6,  9, 16]    =》   [3,   6,  9, 16]
  [10, 13, 14, 17, 24],         [10, 13, 14, 17, 24],         [10, 13, 14, 17]          [10, 13, 14, 17]
  [18, 21, 23, 26, 30]          [18, 21, 23, 26, 30]          [18, 21, 23, 26]          [18, 21, 23, 26]


 不会在第三行往左出现 16 < 18       不会在第四行往左出现 17 < 18
  =》 [10, 13, 14, 17]      =》                                ... =》 
      [18, 21, 23, 26]               [18, 21, 23, 26]                [18]
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        for(int i =0 , j = matrix[0].size()-1; i<matrix.size() && j>=0;){
            if(matrix[i][j] == target) return true;
            if(matrix[i][j] < target) i++;
            else j--;
        }
        return false;
    }
};

class Solution {
public:
    bool searchMatrix(int** A, int m, int n, int target) {
        int x = ~target;
        while (m && n && (x = A[0][n-1]) != target)
            x < target ? A++, m-- : n--;
        return x == target;
    }
};