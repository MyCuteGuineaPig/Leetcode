/*
123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


*/



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int K = 2;
        vector<vector<int>>dp(K+1, vector<int>(prices.size(),0));    
        for(int k = 1; k<= K; k++){
            int tmax = -prices[0];
            for(int i = 1; i<prices.size();i++){
                dp[k][i] = max(dp[k][i-1],tmax+prices[i]);
                tmax = max(tmax, dp[k-1][i]-prices[i]);
            }
        }
        return dp[2][prices.size()-1];
    }
};
                    

/*

         3,   1,   4,   8,   7,   2,   9,    3,    4
  tmax   -3  - 1   -1   -1   -1   -1   -1   -1   -1
  ff[1]  0    0     3    7   7     7   8     8     8
  tmax   -3  - 1   -1   -1   0    5    5     5     5
  ff[2]  0    -1   3    7    7    7    14   14     14

   tmpMax = max(tmpMax, f[k-1][i] - prices[i]);  表示如果上一次到i的利润是f[k-1][i]，我现在在此利润基础上找价格低点
   比如 price = 2, ff[1] = 7, 价格差5，再次基础上抛售上一个，买近下一个,现在利润是7，用现在利润7买进2，还剩下5，

*/