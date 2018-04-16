/*
368. Largest Divisible Subset

Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:
 Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)
Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]

*/

/*
tricky 先sort，然后后面的大的，只要除以subset中最大的数，就可以append进subset，比如【1,2,4,7,8] 到4结束有3个，到8时候，只要8可以除以4，就可以在加上一个
用一个parent vector，放这个subset得上一个数的位置

*/

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        sort(nums.begin(),nums.end());
        vector<int>dp(nums.size(),1) ;//存到i点最多可以有几个subset
        vector<int>prev(nums.size(),-1);
        int largest_index = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]%nums[j] == 0 && dp[i]<dp[j]+1){
                    dp[i] = dp[j]+1;
                    prev[i] = j;
                }   
            }
            if(dp[largest_index]<dp[i])
                largest_index = i;
        }
        
        vector<int>res;
        for(int i = largest_index;i!=-1; i = prev[i])
            res.push_back(nums[i]);
        return res;
    }
};



static int x = [](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return {};
        sort(nums.begin(),nums.end());
        vector<int>dp(nums.size(),1) ;//存到i点最多可以有几个subset
        vector<int>prev(nums.size(),-1);
        int largest_index = 0;
        for(int i = 0; i<nums.size();i++){
            for(int j = 0; j<i; j++){
                if(nums[i]%nums[j] == 0 && dp[i]<dp[j]+1){
                    dp[i] = dp[j]+1;
                    prev[i] = j;
                }   
            }
            if(dp[largest_index]<dp[i])
                largest_index = i;
        }
        
        vector<int>res;
        for(int i = largest_index;i!=-1; i = prev[i])
            res.push_back(nums[i]);
        return res;
    }
};