/*
47. Permutations II


Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]


*/


class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>res;
        backtracking(nums, res, 0);
        return res;
    }
    
private:
    void backtracking(vector<int>& nums, vector<vector<int>>& res,int begin){
        if(begin==nums.size()-1){
            res.push_back(nums);
            return;
        }
        for(int i = begin; i<nums.size();i++){
            if((nums[i]!=nums[begin] || i == begin) && checkmiddle(nums,i,begin)){
                swap(nums[i],nums[begin]);
                backtracking(nums, res, begin+1);
                swap(nums[i],nums[begin]);
            }
        }
        
    }
    
    bool checkmiddle(vector<int>& nums, int i , int begin){
        for(int k = begin; k<i; k++)
            if(nums[i] == nums[k])
                return false;
        return true;
    }
};

class Solution {
public:
    void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) { //non reference num
        if (i == j-1) {
            res.push_back(num);
            return;
        }
        for (int k = i; k < j; k++) {
            if (i != k && num[i] == num[k]) continue;
            cout<<" swap begin "<<i<<" i "<<k<<endl;
            printnum(num);
            swap(num[i], num[k]);
            cout<<"    after swap  "<<endl<<"    ";
            printnum(num);
           
            recursion(num, i+1, j, res);
            cout<<" back "<<i<<" i "<<k<<endl;
        }
    }
    vector<vector<int> > permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        vector<vector<int> >res;
        recursion(num, 0, num.size(), res);
        return res;
    }

     
    void printnum(vector<int> &nums){
        for(auto i : nums){
            cout<<i<<"  ";
        }
        cout<<endl;
    }
};

 swap begin 0 i 0
1  1  2  2  
    after swap  
    1  1  2  2  
 swap begin 1 i 1
1  1  2  2  
    after swap  
    1  1  2  2  
 swap begin 2 i 2
1  1  2  2  
    after swap  
    1  1  2  2  
 back 2 i 2
 back 1 i 1
 swap begin 1 i 2
1  1  2  2  
    after swap  
    1  2  1  2  
 swap begin 2 i 2
1  2  1  2  
    after swap  
    1  2  1  2  
 back 2 i 2
 swap begin 2 i 3
1  2  1  2  
    after swap  
    1  2  2  1  
 back 2 i 3
 back 1 i 2
 back 0 i 0
 swap begin 0 i 2
1  1  2  2  
    after swap  
    2  1  1  2  
 swap begin 1 i 1
2  1  1  2  
    after swap  
    2  1  1  2  
 swap begin 2 i 2
2  1  1  2  
    after swap  
    2  1  1  2  
 back 2 i 2
 swap begin 2 i 3
2  1  1  2  
    after swap  
    2  1  2  1  
 back 2 i 3
 back 1 i 1
 swap begin 1 i 3
2  1  1  2  
    after swap  
    2  2  1  1  
 swap begin 2 i 2
2  2  1  1  
    after swap  
    2  2  1  1  
 back 2 i 2
 back 1 i 3
 back 0 i 2
