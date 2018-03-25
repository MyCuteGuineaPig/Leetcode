/*
329. Longest Increasing Path in a Matrix.cpp

Time	    Space	    Difficulty
O(m * n)	O(m * n)	Hard

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.

*/

/**
 * 
 * some observations:
https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C++
The nodes which have odd degrees (int and out) are the entrance or exit. In your example it’s JFK and A.

If there are no nodes have odd degrees, we could follow any path without stuck until hit the last exit node

The reason we got stuck is because that we hit the exit

In your given example, nodes A is the exit node, we hit it and it’s the exit. So we put it to the result as the last node.
*/

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>>m; 
        vector<string>res;
        for(auto t: tickets){
            m[t.first].push(t.second);
        }
        dfs("JFK", res, m);
        reverse(res.begin(),res.end());
        return res;
    }

     void dfs(string cur, vector<string>& res, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& m)      {
        //cout<<"cur " << cur <<endl;
        while(!m[cur].empty()){
            string s = m[cur].top();
            m[cur].pop();
            //cout<<"before dsf cur "<<cur<<" size "<<m[cur].size()<<endl;
            dfs(s, res, m);
            //cout<<"after dfs "<<cur<<" size "<<m[cur].size()<<endl;
        }
        //cout<<"push back "<<cur<<endl;
        res.push_back(cur);
    }
};