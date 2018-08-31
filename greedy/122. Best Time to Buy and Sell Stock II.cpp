/*
122. Best Time to Buy and Sell Stock II
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit.
 You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). 
 However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1) return 0;
        int profit = 0;
        for(int i = 1; i<prices.size();i++){
            if(prices[i]>prices[i-1])
                profit += prices[i]-prices[i-1];
        }
        return profit;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        int prev = prices[0], tot = 0;
        for(auto p: prices){
            tot += max(p - prev,0);
            prev = p;
        }
        return tot;
    }
};

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int ret = 0;
        for (size_t p = 1; p < prices.size(); ++p) 
        ret += max(prices[p] - prices[p - 1], 0);    
        return ret;
    }
};

/*
The greedy pair-wise approach mentioned in other posts is great for this problem indeed, 
but if we're not allowed to buy and sell stocks within the same day it can't be applied 
(logically, of course; the answer will be the same). 
Actually, the straight-forward way of finding next local minimum and next local maximum is not much more complicated, 
so, just for the sake of having an alternative I share the code in Java for such case.

*/

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int profit = 0, i = 0;
        while (i < prices.size()) {
            // find next local minimum
            while (i < prices.length-1 && prices[i+1] <= prices[i]) i++;
            int min = prices[i++]; // need increment to avoid infinite loop for "[1]"
            // find next local maximum
            while (i < prices.length-1 && prices[i+1] >= prices[i]) i++;
            profit += i < prices.length ? prices[i++] - min : 0;
        }
        return profit;
    }
};
