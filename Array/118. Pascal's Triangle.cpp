/*
118. Pascal's Triangle


Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]


*/



class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>res;
        for(int i = 1; i<=numRows; i++){
            vector<int>temp;
            for(int j = 0; j<i; j++){
                if(j == 0 || j == i-1) temp.push_back(1);
                else temp.push_back(res.back()[j-1] + res.back()[j]);
            }
            res.push_back(temp);
        }
        return res;
    }
};