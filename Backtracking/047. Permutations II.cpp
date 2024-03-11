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

主要逻辑是: 如果一个数被换到index 位置，那么与这个数相同的不能再被换

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
        unordered_set<int>st;
        for(int i = begin; i<nums.size();i++){
            if( st.count(nums[i])== 0 ){
                st.insert(nums[i]);
                swap(nums[i],nums[begin]);
                backtracking(nums, res, begin+1);
                swap(nums[i],nums[begin]);
            }
        }
        
    }
};



class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>>res; //不需要sort
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
    /*
    如果没有check middle的话, 比如 
    [ 0 0 1 1 2 2]
    现在index 0 和  index 5换 
      -> 2 0 1 1 0 2    ->  0 1 1 0 变成不sort的了， 
      
       2 0 1 1 0 2   ->  再 index 1 和 index 2 换, 变成 2 1 0 1 0 2
       
       2 0 1 1 0 2   ->  index 0 和 index 3 换 -> 2 1 1 0 0 2 -> index 2 和 index 3 换 2 1 0 1 0 2 和上面重复了
    

    比如 nums = [9, 0, 1, 0] 第二个0 会和第四个0 换


    */
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
            //printnum(num);
            swap(num[i], num[k]);
            //printnum(num);
           
            recursion(num, i+1, j, res);
            /*
            如果换回去的话，无法保证已经proceed的数 不再proceed 比如 
            9 0 1 0 => 0 9 1 0  (index 0 和 index 1 换)
            如果再换回 9 0 1 0 
            等 k = 3, index 0 和 index 3 换，又是9 0 1 0 
            
            */
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


/*
为什么不swap back
for list nums = [1, 2, 2]
() mean i, <> mean pos
step 1
i=0,pos=0,swap(i,pos)              |    i=1,pos=0,swap(i,pos)          |       i=2,pos=0,swap(i,pos)
[(<1>), 2, 2]                      |    [<2>, (1), 2]                  |       [<2>, 1, (2)]
step 2                             |                                   |
i=1,pos=1     |  i=2,pos=1         |    i=1,pos=1     |  i=2,pos=1     |       nums[2]=nums[pos]
[1, (<2>), 2] |  [1, <2>, (2)]     |    [2, <(1)>, 2] |  [2, <2>, (1)] |       no out put
step 3        |                    |                  |                |
i=2,pos=2     |                    |    i=2,pos=2     |  i=2,pos=2     |
[1, 2, (<2>)] |  nums[2]=nums[pos] |    [2, 1, (<2>)] |  [2, 2, (<1>)] |
     ouput    |  no output return  |    ouput         |  ouput         |
*/



//copy by reference
class Solution {
public:
    void helper(vector<vector<int>>& res, vector<int>& nums, int pos) {
        
        if (pos == nums.size()) {
            res.push_back(nums);
        } else {
            for (int i = pos; i < nums.size(); ++i) {
                if (i > pos && nums[i] == nums[pos]) continue;
                swap(nums[pos], nums[i]);
                helper(res, nums, pos + 1);

            }
            // restore nums
            for (int i = nums.size() - 1; i > pos; --i) {
                swap(nums[pos], nums[i]);
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        helper(res, nums, 0);
        return res;
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
