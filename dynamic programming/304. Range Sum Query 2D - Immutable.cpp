/*
304. Range Sum Query 2D - Immutable
https://leetcode.com/problems/range-sum-query-2d-immutable/description/

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2

*/


class NumMatrix {
public:
    vector<vector<int>>dp;
    NumMatrix(vector<vector<int>> matrix) {
        
        if(matrix.size()>0 && matrix[0].size()>0){
            dp.resize(matrix.size(), vector<int>(matrix[0].size(),0));
            for(int i = 0; i<matrix.size();i++){
                for(int j = 0; j<matrix[0].size();j++){
                    if(i == 0){
                        dp[i][j] = dp[i][j-1]+matrix[i][j];
                    }
                    else if(j == 0){
                        dp[i][j] = dp[i-1][j]+matrix[i][j];
                    }
                    else if(i!=0 && j!=0){
                         dp[i][j] = dp[i-1][j]+matrix[i][j] +dp[i][j-1] - dp[i-1][j-1] ;
                    }
                }
            }
        }
            
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2][col2] - (row1==0 ? 0 : dp[row1-1][col2] ) - (col1==0 ? 0 : dp[row2][col1-1]) + (col1!=0 && row1!= 0 ?dp[row1-1][col1-1]: 0);
    }
};

/*

Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]


  sum matrix = [
 3  3    4   8   10  
 8  14   18  24  27  
 9  17   21  28  36  
 13  22  26  34  49  
 14  23  30  38  58  



*/