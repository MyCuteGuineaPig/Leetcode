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

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int K = 2;
        vector<vector<int>>dp(K+1, vector<int>(prices.size(),0));    
        for(int k = 1; k<= K; k++){
            int tmax = -prices[0];
            for(int i = 1; i<prices.size();i++){
                tmax = max(tmax, dp[k-1][i-1]-prices[i]);
                dp[k][i] = max(dp[k][i-1],tmax+prices[i]);
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


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1) return 0;
        vector<int>profit(prices.size(),0);
        for(int k = 0; k<2; k++)
            for(int i = 1, cost = -prices[0], prev_cost = -prices[0]; i<prices.size();prev_cost = cost,i++)
                cost = max(profit[i]-prices[i],cost), profit[i] = max(profit[i-1],prices[i] + prev_cost);
        
        return profit[prices.size()-1];
    }
};

/*
         1   2   3    2   5  1 6
i = 0
    cost -1 -1  -1   -1  -1 -1 -1    到每个点用profit 价格，等于剩余的profit
    dp   0   1   2    2   4  4  5
i = 1
    cost -1 -1  -1    0   0  3  0 
    dp   0   1   2    2   5  5  9

每个loop 都可以保证是最多i个transaction，因为每个loop的profit的 前提是基于i-1个transaction的,而每个loop 只会增加一个transaction，
因为每个loop 的原则是找到新的最低点，然后买进，再卖出
*/



/**

It's not difficult to get the DP recursive formula:

dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j-1]), j=[0..i-1]

For k transactions, on i-th day,

if we don't trade then the profit is same as previous day dp[k, i-1];
and if we bought the share on j-th day where j=[0..i-1], then sell the share on i-th day 
then the profit is prices[i] - prices[j] + dp[k-1, j-1] .

Actually j can be i as well. When j is i, the one more extra item prices[i] - prices[j] + dp[k-1, j] = dp[k-1, i]
looks like we just lose one chance of transaction.

I see someone else use the formula 
dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j]), where the last one is dp[k-1, j] instead of dp[k-1, j-1]. 
It's not the direct sense, as if the share was bought on j-th day, 
then the total profit of previous transactions should be done on (j-1)th day. 
However, the result based on that formula is also correct, 
because if the share was sold on j-th day and then bought again, it is the same if we didn't trade on that day.

So the straigtforward implementation is:
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int K = 2;
        vector<vector<int>>dp(K+1, vector<int>(prices.size(),0));    
        for (int k = 1; k <= 2; k++)  {
            for (int i = 1; i < prices.size(); i++) {
                int cost = prices[0];
                for (int j = 1; j <= i; j++)
                    cost = min(cost, prices[j] - dp[k-1][j-1]);
                dp[k][i] = max(dp[k][i-1], prices[i] - cost);
            }
        }

        return dp[K][prices.size() - 1];
    }
};

/**
Time complexity is O(kn^2), space complexity is O(kn).
In the above code, min is repeated calculated. It can be easily improved as:
 */


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int K = 2;
        vector<vector<int>>dp(K+1, vector<int>(prices.size(),0));    
        for (int k = 1; k <= 2; k++)  {
            int cost = prices[0];
            for (int i = 1; i < prices.size(); i++) {
                cost = min(cost, prices[i] - dp[k-1][i-1]);
                dp[k][i] = max(dp[k][i-1], prices[i] - cost);
            }
        }

        return dp[K][prices.size() - 1];
    }
};

/**
Time complexity is O(kn), space complexity is O(kn).
If we slight swap the two 'for' loops:
 */


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int K = 2;
        vector<vector<int>>dp(K+1, vector<int>(prices.size(),0));   
        vector<int>cost(K+1,0);
        for(int k = 1; k<=2; ++k)
            cost[k] = prices[0];
        for (int i = 1; i < prices.size(); i++)  {
            for (int k = 1; k <= 2; k++) {
                cost[k] = min(cost[k], prices[i] - dp[k-1][i-1]);
                dp[k][i] = max(dp[k][i-1], prices[i] - cost[k]);
            }
        }

        return dp[K][prices.size() - 1];
    }
};

/*
We need to save min for each transaction, so there are k 'min'.
We can find the second dimension (variable i) is only dependent on the previous one (i-1), 
so we can compact this dimension. 

(We can choose the first dimension (variable k) as well since it is also only dependent on its previous one k-1, 
but can't compact both.)
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int K = 2;
        vector<int>dp(K+1,0);   
        vector<int>cost(K+1,0);
        for(int k = 1; k<=2; ++k)
            cost[k] = prices[0];
        for (int i = 1; i < prices.size(); i++)  {
            for (int k = 1; k <= 2; k++) {
                cost[k] = min(cost[k], prices[i] - dp[k-1]);
                dp[k] = max(dp[k], prices[i] - cost[k]);
            }
        }

        return dp[K];
    }
};

/**
 So time complexity is O(kn), space complexity becomes O(k).
In this case, K is 2. We can expand the array to all named variables:
 */

//任意排列组合 buy1, sell1, buy2, sell2都可以
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int buy1 = prices[0];
        int buy2 = prices[0];

        int sell1 = 0, sell2 = 0;

        
        for (int i = 1; i < prices.size(); i++)  {
            buy1 = min(buy1, prices[i]);   //sell1, buy1 不会同时get update, 因为低点才能买，高点才能卖，不会同时低点高点
            sell1 = max(sell1, prices[i] - buy1);
            
            buy2 = min(buy2, prices[i] - sell1); //buy2 和 sell1 order, doesn't matter, 不会同时update
            /**
             *  Assumption :  1. sell1 always positive, sell1 < prices[i], 
             *             2. buy1 = prices[i] - sell1 if sell1 get updated , 
             *             3. buy2 <= buy1,  初始值 buy2 = buy1, 但有了一些profit (sell1), 
             *                               prices[i] - sell1 < prices[i]             =>  buy2 <= buy1 
             * 
             * When sell1 get update, buy1 = prices[i] - sell1:
             *         so  buy2 <= buy1 = prices[i] - sell1, buy2 won't get updated 
             */

            sell2 = max(sell2, prices[i] - buy2); //sell2 和 buy2 不会同时update
            /** Assumption:
             *             1.  sell2 = sell1 at beginning e.g. [1,3], 因为buy1 = buy2 = 1
             *             2.  sell2 >= sell1: 因为sell1 always positive, 
             *                          then prices[i] - sell1 < prices[i]              => buy2 <= buy1, 
             *                                prices[i] - buy2 < = prices[i] - buy1     => sell2 > sell1
             *  
             * Then when buy2 get update  buy2 = prices[i] - sell1
             *             Then prices[i] - buy2  = prices[i] - (prices[i] - sell1)
             *                                    = sell1 
             *                                    <= sell2     =>sell2 won't get update 
             *             
             */
        }

        return sell2;
    }
};

/*
Order Doesn't matter, since if it is buy point, it won't be sell point;
If it is a sell point, it won't be a buy point
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int buy1 = prices[0];
        int buy2 = prices[0];

        int sell1 = 0, sell2 = 0;

        
        for (int i = 1; i < prices.size(); i++)  {
            
            sell1 = max(sell1, prices[i] - buy1);
            sell2 = max(sell2, prices[i] - buy2);
            
            
            buy2 = min(buy2, prices[i] - sell1);
            buy1 = min(buy1, prices[i]);
        }
        return sell2;
    }
};

/**
 Then the tricky part comes, how to handle the twoBuy? 
 Suppose in real life, you have bought and sold a stock and made $100 dollar profit. 
 When you want to purchase a stock which costs you $300 dollars, 
how would you think this? You must think, um, I have made $100 profit, so I think this $300 dollar stock is worth $200 FOR ME 
since I have hold $100 for free.

There we go, you got the idea how we calculate twoBuy!! We just minimize the cost again!! 
The twoBuyTwoSell is just making as much profit as possible.
Hope this explanation helps other people to understand this!
 */




/**
 * Good Diagram and explanation:
 * 1. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
 * 
 * 2. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/149383/Easy-DP-solution-using-state-machine-O(n)-time-complexity-O(1)-space-complexity
 */

