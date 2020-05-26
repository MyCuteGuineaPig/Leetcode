/*

This dp works in this way: we scan the array from len 2 to len n with all possible start points and end points.
 For each combination, we will find the best way to burst balloons. 
 dp[i][j] means we are looking at a combination with start point at index i and end point at index j with len of j - i.
  In this combination, we use the third loop to find the best way to burst. 
  “nums[left] * nums[i] * nums[right]” means we burst all balloons from left to i and all ballons from i to right. 
  So only balloons left, i and right exits in current combination therefore we can do this operation.
   “+ dp[left][i] + dp[i][right]” means add the value from best burst in range(left, i) and range(i, right).

Hope this help

*/


class Solution {
public:
    int maxCoins(vector<int> &iNums) {
    int nums[iNums.size() + 2];
    int n = 1;
    for (int x : iNums) //if (x > 0) 
        nums[n++] = x;
    nums[0] = nums[n++] = 1;

    int dp[n][n] = {};
    for (int k = 2; k < n; ++k) {
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