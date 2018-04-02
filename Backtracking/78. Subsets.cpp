/*

78. Subsets

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]


*/


/*
backtracking 不需要sort

*/


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //sort(nums.begin(),nums.end());
        vector<int> cur; 
        vector<vector<int>>res;
        backtrack(nums, res, cur, 0);
        return res;
    }
    
    void backtrack(vector<int>& nums,vector<vector<int>>& res,vector<int>& cur, int begin){
        res.push_back(cur);
        for(int i = begin; i<nums.size();i++){
            cur.push_back(nums[i]);
            backtrack(nums,res,cur,i+1);
            cur.pop_back();
        }
    }
};


/*
Iterative solution: 

This problem can also be solved iteratively. Take [1, 2, 3] in the problem statement as an example. The process of generating all the subsets is like:

Initially: [[]]
Adding the first number to all the existed subsets: [[], [1]];
Adding the second number to all the existed subsets: [[], [1], [2], [1, 2]];
Adding the third number to all the existed subsets: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]].

*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>res(1, vector<int>());
        for(int i: nums){
            int size = res.size();
            for(int j = 0; j<size; j++){
                res.push_back(res[j]);
                res.back().push_back(i);
            }
            
        }
        
        return res;
    }
};


/*

bitmask

Bit Manipulation

This is the most clever solution that I have seen. The idea is that to give all the possible subsets, we just need to exhaust all the possible combinations of the numbers. And each number has only two possibilities: either in or not in a subset. And this can be represented using a bit.

There is also another a way to visualize this idea. That is, if we use the above example, 1 appears once in every two consecutive subsets, 2 appears twice in every four consecutive subsets, and 3 appears four times in every eight subsets, shown in the following (initially the 8 subsets are all empty):

[], [], [], [], [], [], [], []

[], [1], [], [1], [], [1], [], [1]

[], [1], [2], [1, 2], [], [1], [2], [1, 2]

[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]

*/


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = pow(2,nums.size());
        vector<vector<int>>res(n,vector<int>());
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<n; j++){
                if((j>>i) & 1)
                    res[j].push_back(nums[i]);
            }
        }
        return res;
    }
    
};
