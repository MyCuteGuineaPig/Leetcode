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




class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() ==0) return 0;
        vector<int>dp(triangle.size()+1,0);
        for(int i = triangle.size()-1; i>=0; i--)
            for(int j = 0; j<triangle[i].size();j++)
                dp[j] = min(dp[j],dp[j+1]) + triangle[i][j];
        return dp[0];
    }
};


/*
No extra space 
*/


class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() ==0) return 0;
        for(int i = triangle.size()-2; i>=0; i--)
            for(int j = 0; j<triangle[i].size();j++)
                triangle[i][j] = min(triangle[i+1][j],triangle[i+1][j+1]) + triangle[i][j];
        return triangle[0][0];
    }
};