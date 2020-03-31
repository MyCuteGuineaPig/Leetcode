/*
714. Best Time to Buy and Sell Stock with Transaction Fee

Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i; 
and a non-negative integer fee representing a transaction fee.

You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction. 
You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Note:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.



*/



/*
            1, 3, 2, 8, 4, 9 
    buy  0  3  3  3  3  1  1
    sell 0  0  0  0  5  5  8


*/


class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<int>buy(prices.size()+1, INT_MAX);
        vector<int>sell(prices.size()+1);
        for(int i = 0; i<prices.size();i++){
            buy[i+1] = min(buy[i], prices[i]+fee-sell[i]);
            sell[i+1] = max(sell[i], prices[i]-buy[i]);
        }
        return sell.back();
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int buy = INT_MAX, sell = 0, prevbuy = INT_MAX;
        for(int i = 0; i<prices.size();i++){
            prevbuy = buy;
            buy = min(buy, prices[i]-sell+fee);
            sell = max(sell, prices[i]-prevbuy);
        }
        return sell;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int buy = INT_MAX, sell = 0;
        for(int i = 0; i<prices.size();i++){
            buy = min(buy, prices[i]-sell+fee); //buy 和sell 只会变化一个
            sell = max(sell, prices[i]-buy);
        }
        return sell;
    }
};