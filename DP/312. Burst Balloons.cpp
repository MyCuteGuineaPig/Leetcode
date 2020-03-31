
/*
312. Burst Balloons
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. 
You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

*/


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

    //cout<<" n "<<n<<endl;
    int dp[n][n] = {};
    for (int k = 2; k < n; ++k) {
        for (int left = 0; left < n - k; ++left){
            int right = left + k;
            for (int i = left + 1; i < right; ++i){
                //cout<<"left "<<left<<" i "<<i<<" right "<<right<< " left*i*right "<<nums[left] * nums[i] * nums[right] <<" dp[left][i] "<<dp[left][i]<<" dp[i][right] "<<dp[i][right]<<" dp[left][right] "<<dp[left][right]<<endl;
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
                    //cout<<" leftnum "<<leftnum<<" nums[i] "<<nums[i]<<" right num "<<rightnum<<endl;
                    //cout<<"left "<<left<<" i "<<i<<" right "<<right<< " left*i*right "<<leftnum* nums[i-1] *rightnum <<" dp[left][i] "<<dp[left][i]<<" dp[i][right] "<<dp[i][right]<<" dp[left][right] "<<dp[left][right]<<endl;
                
                    dp[left][right]=max(dp[left][right],dp[left][i] + dp[i][right] + leftnum*nums[i-1]*rightnum);
                }
            }            
        }
        return dp[0][nums.size()+1];
    }
};