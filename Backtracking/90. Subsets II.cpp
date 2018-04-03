/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

*/


class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<int>cur;
        vector<vector<int>>res;
        backtracking(nums,res,cur,0);
        return res;
    }
    
    void backtracking(vector<int>& nums, vector<vector<int>>&res, vector<int>&cur, int begin){
        res.push_back(cur);
        int prevchange = INT_MAX;
        for(int i = begin; i<nums.size();i++){
            if(nums[i]!=prevchange){
                prevchange =  nums[i];
                cur.push_back(nums[i]);
                backtracking(nums,res,cur,i+1);
                cur.pop_back();
            }
        }
        
    }
};



/*
iterative 
*/

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& S) {
        sort(S.begin(), S.end());
        vector<vector<int>> ret = {{}};
        int size = 0, startIndex = 0;
        for (int i = 0; i < S.size(); i++) {
            startIndex = i >= 1 && S[i] == S[i - 1] ? size : 0; //要是与之前重复的话，插入与之前一样的起始位置开始插入
            size = ret.size();
            //cout<<" i "<<i<<" startIndex "<<startIndex<<"  size "<<size<<endl;
            for (int j = startIndex; j < size; j++) {
                vector<int> temp = ret[j];
                temp.push_back(S[i]);
                ret.push_back(temp);
            }
        }
        return ret;
    }
};


/**
 To solve this problem, it is helpful to first think how many subsets are there. 
 If there is no duplicate element, the answer is simply 2^n, where n is the number of elements. 
 This is because you have two choices for each element, either putting it into the subset or not. 
 So all subsets for this no-duplicate set can be easily constructed:
num of subset

(1 to 2^0) empty set is the first subset
(2^0+1 to 2^1) add the first element into subset from (1)
(2^1+1 to 2^2) add the second element into subset (1 to 2^1)
(2^2+1 to 2^3) add the third element into subset (1 to 2^2)
…
(2^(n-1)+1 to 2^n) add the nth element into subset(1 to 2^(n-1))
Then how many subsets are there if there are duplicate elements? We can treat duplicate element as a spacial element. 
For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, 
we can treat it as one special element 5, but this element has more than two choices:
 you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. 
 Therefore, we are given an array (a1, a2, a3, …, an) with each of them appearing (k1, k2, k3, …, kn) times, 
 the number of subset is (k1+1)(k2+1)…(kn+1). We can easily see how to write down all the subsets similar to the approach above.
*/

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>res={{}};
        for(int i = 0; i<nums.size();){
            int count = 0;
            for(;count+i<nums.size()&& nums[i+count] == nums[i]; count++);
            int size_0 = res.size();
            for(int j = 0; j<size_0; j++){
                vector<int>temp = res[j];
                for(int k = 0; k<count;k++){
                    temp.push_back(nums[i]);
                    res.push_back(temp);
                }
            }
            i+= count;
        }
        return res;
    }
};

