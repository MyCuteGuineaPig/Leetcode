/*
216. Combination Sum III

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]



*/


class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>>res;
        vector<int>cur;
        backtracking(res,cur,k,n,1);
        return res;
    }
    
    void backtracking(vector<vector<int>>& res, vector<int>& cur, int k, int n, int num){
        if(k == 0 && n==0) 
            res.push_back(cur);
        for(int i = num; i<=9 && i<=n && k>=0; i++){
            cur.push_back(i);
            backtracking(res, cur, k-1, n-i, i+1);
            cur.pop_back();
        }
        
    }
};

