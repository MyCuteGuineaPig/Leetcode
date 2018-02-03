/*
120. Triangle
https://leetcode.com/problems/triangle/description/

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int>cur(triangle.size());
        for(int i = triangle.size()-1;i>=0; i--){
            for(int j = 0;j<=i;j++){
                if(i==triangle.size()-1){
                    cur[j] = triangle[i][j];
                }else{
                    cur[j] = triangle[i][j]+min(cur[j],cur[j+1]);
                }
            }
        }
        return cur[0];
    }
};