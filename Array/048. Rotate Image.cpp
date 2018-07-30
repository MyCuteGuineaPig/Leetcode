/*
48. Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
Example 2:

Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]


*/



/*

转圈改，


（i,j) <- (n-1-j, i)  左半块

(n-1-j, i)  <- （n-1-i, n-1-j) 下半块

（n-1-i, n-1-j) <-  (j, n-1-i)  右半块

(j, n-1-i) <- （i,j) 

详解见   048. Rotate Image
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i<n/2; i++){
            for(int j = i; j<n-1-i; j++){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = temp;
            }
        }
    }
};

class Solution {
public:
    void _swap(int *a,int *b, int *c, int *d){
        int t=*d;
        *d=*c;
        *c=*b;
        *b=*a;
        *a=t;
    }
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        for(int i=0;i<n/2;i++){
            for(int j=0;j<n-2*i-1;j++){
                _swap(&matrix[i][i+j],&matrix[i+j][n-i-1],&matrix[n-i-1][n-i-1-j],&matrix[n-i-1-j][i]);
            }
        }
    }
};

/*

先以对角线转，然后上下翻个
比如
      1   2   3
      4   5   6
      7   8   9


rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
*/


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n-1-i; j++){
                swap(matrix[i][j], matrix[n-1-j][n-1-i]);
            }
        }
        for(int i = 0; i<n/2; i++){
            for(int j = 0; j<n; j++){
                swap(matrix[i][j], matrix[n-1-i][j]);
            }
        }
    }
};