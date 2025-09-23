

/*
            1, 3, 2, 8, 4, 9 
    buy  0  3  3  3  3  1  1
    sell 0  0  0  0  5  5  8


*/

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int buy = numeric_limits<int>::max();
        int sell = 0;
        for(int i = 0; i < prices.size(); ++i){
            buy = min(buy, prices[i]-sell + fee);
            sell = max(sell, prices[i]- buy);
        }
        return sell;
    }
};


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
            sell = max(sell, prices[i]-buy);// buy 更新因为遇到低的价格, 低的价格不会卖
        }
        return sell;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& p, int fee) {
        int n = p.size();
        if (n < 2) return 0;
        vector<int> buy(n, 0), sell(n, 0);
        buy[0] = -p[0];
        for (int i = 1; i < n; i++) {
            buy[i] = max(buy[i - 1], sell[i - 1] - p[i]);
            sell[i] = max(sell[i - 1], buy[i - 1] - fee + p[i]);
        }

        return sell[n - 1];
    }
};