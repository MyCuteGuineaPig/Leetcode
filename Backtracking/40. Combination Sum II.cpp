/*
40. Combination Sum II


Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]


*/

class Solution {
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>res;
        vector<int>cur;
        backtrack(candidates,res,cur,target,0);
        return res;
    }

    void backtrack(vector<int>& candidates, vector<vector<int>>& res, vector<int>& cur, int target, int index){
        if(target<0) return;
        if(target == 0) res.push_back(cur);
        for(int i = index; i<candidates.size() && target >= candidates[i];i++){
            if(i==index || candidates[i]!=candidates[i-1]){ // candidates[i] == candidates[i-1] 舍弃上一个，拿下一个一样的
                //i==index 有可能一样的，但是是append进来的，而不是舍弃上一个一样的，加下一个
                cur.push_back(candidates[i]);
                backtrack(candidates,res,cur,target-candidates[i],i+1);
                cur.pop_back();
            }
        }
    }
};