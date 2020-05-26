/*

dp[i][j] 表示从 i 到 j 最大Burst Ballons 的数
dp[i][j]: coins obtained from bursting all the balloons between index i and j (not including i or j)


*/


// Bottom-Up, left 表示 
class Solution {
public:
    int maxCoins(vector<int> &iNums) {
    int nums[iNums.size() + 2];
    int n = 1;
    for (int x : iNums) //if (x > 0) 
        nums[n++] = x;
    nums[0] = nums[n++] = 1;

    int dp[n][n] = {};
    for (int k = 2; k < n; ++k) { // k = 2 起 表示 长度为1的ballon array, 因为不包括left, right, 
        for (int left = 0; left < n - k; ++left){
            int right = left + k;
            for (int i = left + 1; i < right; ++i){
                dp[left][right] = max(dp[left][right],
                     nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
            }
        }
    }

    return dp[0][n - 1];
}
};

// Bottom-Up
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<vector<int>>dp(nums.size()+2,vector<int>(nums.size()+2,0));
        for(int k = 2; k<nums.size()+2;k++){
            for(int left = 0; left+k<nums.size()+2;left++){
                int right = left+k;
                for(int i = left+1; i<right;i++){
                    int leftnum = 1,rightnum=1;
                    if(left != 0) leftnum = nums[left-1];
                    if(right!=nums.size()+1) rightnum = nums[right-1];
                    
                    dp[left][right]=max(dp[left][right],dp[left][i] + dp[i][right] + leftnum*nums[i-1]*rightnum);
                }
            }            
        }
        return dp[0][nums.size()+1];
    }
};

//2020 Top-Down:  dp[i][j] include i and j
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        if(nums.empty()) return 0;
        unordered_map<int,unordered_map<int,int>>dp;
        return topDown(nums,dp,0,nums.size()-1);
    }
    
    int topDown(const vector<int>& nums, unordered_map<int,unordered_map<int,int>>&dp, int left, int right){
        if(left > right)
            return 0;

        if(dp.count(left) && dp[left].count(right))
            return dp[left][right];
        
        int cur = 0;
        for(int i = left; i<=right; ++i){
            int leftnum =  left == 0 ? 1: nums[left-1];
            int rightnum = right == nums.size()-1 ? 1: nums[right+1];
            cur = max(cur, leftnum*nums[i]*rightnum + topDown(nums,dp,left, i-1) + topDown(nums, dp, i+1, right));
        }
        return dp[left][right] = cur;
    }
};