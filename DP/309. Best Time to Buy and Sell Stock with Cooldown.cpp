/*
309. Best Time to Buy and Sell Stock with Cooldown
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like
 (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]

*/


/*

The series of problems are typical dp. The key for dp is to find the variables to represent the states and
 deduce the transition function.

Of course one may come up with a O(1) space solution directly, but I think it is better to be generous when you think and be greedy when you implement.

The natural states for this problem is the 3 possible transactions : buy, sell, rest. Here rest means no transaction on that day (aka cooldown).

Then the transaction sequences can end with any of these three states.

For each of them we make an array, buy[n], sell[n] and rest[n].

buy[i] means before day i what is the maxProfit for any sequence end with buy.

sell[i] means before day i what is the maxProfit for any sequence end with sell.

rest[i] means before day i what is the maxProfit for any sequence end with rest.

Then we want to deduce the transition functions for buy sell and rest. By definition we have:

buy[i]  = max(rest[i-1]-price, buy[i-1]) 
sell[i] = max(buy[i-1]+price, sell[i-1])
rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
Where price is the price of day i. All of these are very straightforward. They simply represents :

(1) We have to `rest` before we `buy` and 
(2) we have to `buy` before we `sell`
One tricky point is how do you make sure you sell before you buy, since from the equations it seems that [buy, rest, buy] is entirely possible.

Well, the answer lies within the fact that buy[i] <= rest[i] which means rest[i] = max(sell[i-1], rest[i-1]). That made sure [buy, rest, buy] is never occurred.

A further observation is that and rest[i] <= sell[i] is also true therefore

rest[i] = sell[i-1]
Substitute this in to buy[i] we now have 2 functions instead of 3:

buy[i] = max(sell[i-2]-price, buy[i-1])
sell[i] = max(buy[i-1]+price, sell[i-1])
This is better than 3, but


*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        vector<int>buy(prices.size()+1,0);
        vector<int>sell(prices.size()+1,0);
        vector<int>rest(prices.size()+1,0);
        int n = prices.size();
        buy[1] = -prices[0];
        for(int i = 1; i<prices.size(); i++){
            buy[i+1] = max(rest[i]-prices[i], buy[i]);
            sell[i+1] = max(buy[i]+prices[i],sell[i]);
            rest[i+1] = max(max(buy[i],sell[i]), rest[i]);
            //cout<<i<<endl;
            //cout<<"buy "<<buy[i+1]<<" sell "<<sell[i+1] <<" rest "<<rest[i+1]<<endl;
        }
        return  sell[n];
    }
};



/*
buy[i] = max(sell[i-2]-price, buy[i-1])
sell[i] = max(buy[i-1]+price, sell[i-1])

*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        int buy = INT_MIN, prevbuy = 0, sell = 0, prevsell = 0;
        for(int i = 0; i<prices.size(); i++){
            prevbuy = buy;
            buy = max(prevbuy, prevsell - prices[i]);
            prevsell = sell;
            sell = max(prevsell, prevbuy+prices[i]);
        }
        return sell;
    }
};


/*

        [1,   2,   3,   0,   2]
  buy   -1   -1    -1   1    1
  sell   0    1    2    2    3 
  rest   0    0    1    2    2



        [6,   1,   3,   2,   4,   7]
  buy   -6   -1    -1   -1   -1  -1
  sell   0    0    2    2    3   6
  rest   0    0    0    2    2   3



        [6,   1,   3,   5    2,   4,   7]
  buy   -6   -1    -1   -1   0    0    0
  sell   0    0    2    4    4    4    7
  rest   0    0    0    2    4    4    4

*/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        vector<int>buy(prices.size()+1,INT_MAX);
        vector<int>sell(prices.size()+1,0);
        buy[1] = prices[0];
        for(int i = 1; i<prices.size();i++){
            buy[i+1] = min(buy[i],prices[i]-sell[i-1]);
            sell[i+1] = max(sell[i],prices[i]-buy[i]);
        }
        return sell[prices.size()];
    }
};



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        int buy(INT_MAX), sell(0), prev_sell(0), prev_buy(INT_MAX);
        for(int i = 0; i<prices.size();i++){
            prev_buy = buy;
            buy = min(prices[i]-prev_sell, buy);
            prev_sell = sell;
            sell = max(sell,prices[i]-prev_buy);
        }
        return sell;
    }
};