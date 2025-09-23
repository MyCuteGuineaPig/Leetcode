/*

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
        int n = prices.size(); 
        vector<int>buy(n);
        vector<int>sell(n);
        buy[0] = prices[0];
        for(int i = 1; i< n; ++i){
            buy[i] = min(buy[i-1], (i > 1 ? prices[i] - sell[i-2]: prices[i]));                                                                                                                                                                     
            sell[i] = max(sell[i-1], prices[i] - buy[i]);
        }
        return sell.back();
    }
};



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
            // prices[i]-buy[i+1] 也可以，因为update buy[i+1], 表示到新的低点， 新的低点不会是sell点，
            // 如果不更新buy[i+1] (buy[i+1] = buy[i]),  可能是卖点
        }
        return sell[prices.size()];
    }
};


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        int sell(0), prev_sell(0), buy(prices[0]);
        for(int i = 1; i<prices.size();i++){
            buy = min(prices[i]-prev_sell, buy);
            prev_sell = sell;
            sell = max(sell,prices[i]-buy);
        }
        return sell;
    }
};


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
        int buy = INT_MIN, prevbuy = 0, sell = 0, prevsell = 0; //prevsell = sell[i-2]
        for(int i = 0; i<prices.size(); i++){
            prevbuy = buy;
            buy = max(prevbuy, prevsell - prices[i]);
            prevsell = sell;
            sell = max(prevsell, prevbuy+prices[i]);
        }
        return sell;
    }
};

//因为 buy 和 sell 不会同时update, 所以不需要prevbuy
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1 ) return 0;
        int buy = -prices[0], sell = 0, prevsell = 0; //prevsell = sell[i-2]
        for(int i = 1; i<prices.size(); i++){
            buy = max(buy, prevsell - prices[i]);
            prevsell = sell;
            sell = max(prevsell, buy+prices[i]);
        }
        return sell;
    }
};
