/*
46. Permutations

Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]


*/


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        vector<int>cur;
        unordered_set<int>set;
        backtracking(res,nums,cur,set);
        return res;
    }
    
    void backtracking(vector<vector<int>>& res,vector<int>& nums , vector<int> &cur, unordered_set<int>& set){
        if(set.size() == nums.size()) res.push_back(cur);
        for(int i = 0; i<nums.size(); i++){
            if(set.find(nums[i]) == set.end()){
                cur.push_back(nums[i]); set.insert(nums[i]);
                backtracking(res,nums,cur,set);
                cur.pop_back();
                set.erase(nums[i]);
            }
        }
    }
};


/*
用next permutation
*/
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > ans;
        sort(nums.begin(), nums.end());
        ans.push_back(nums);
    
        while(next_permutation(nums.begin(), nums.end()))
            ans.push_back(nums);
        return ans;
    }
    

};




class Solution {
public:
    vector<vector<int> > permute(vector<int> &nums) {
        vector<vector<int> > ans;
        permutation(nums, 0, ans);
        return ans;
    }

    void permutation(vector<int> &nums, int begin, vector<vector<int> > &ans) {
        if (begin >= nums.size()) {
            ans.push_back(nums);
            return;
        }

        // every number chosen to be the begin once
        for (int i = begin; i < nums.size(); ++i) {
            swap(nums[begin], nums[i]);
            
            permutation(nums, begin+1, ans);
            swap(nums[begin], nums[i]);
            
        }
    }
    
    void printnum(vector<int> &nums){
        for(auto i : nums){
            cout<<i<<"  ";
        }
        cout<<endl;
    }
};