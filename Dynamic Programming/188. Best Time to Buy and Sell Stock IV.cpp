/*


Think Process:
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/306282/Different-DP-Python-solutions-with-thinking-process


*/


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(k>prices.size()/2)
        {
            int profit = 0;
            for(int i = 1; i<prices.size();i++){
                profit += max(prices[i]-prices[i-1],0);
            }
            return profit;
        }
        
        if(prices.size()==0) return 0;
        vector<int>dp(prices.size(),0);
        
        for(int n = 1; n<=k && n<prices.size(); n++){
            int tempmax = -prices[0]; //tempmax 相当于negative cost，最小化cost 相当于最大化负的cost
            for(int i = 1; i<prices.size();i++){
                int lastprof = dp[i];
                dp[i] = max(tempmax + prices[i], dp[i-1]);
                tempmax = max(tempmax, lastprof-prices[i]);
            }
        }
        return dp[prices.size()-1];
    }
};

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.size()<=1) return 0;
        if(k>prices.size()/2){
            int profit = 0;
            for(int i = 1; i<prices.size(); i++)
                profit += max(prices[i]-prices[i-1],0);
            return profit;
        }
        vector<int>dp(prices.size(),0);
        for(int a = 0; a<k; a++){
            int cost = prices[0], prev_cost = prices[0];
            for(int i = 1; i<prices.size(); prev_cost = cost, i++){
                cost = min(prices[i]-dp[i],cost); 
                dp[i] = max(prices[i]-prev_cost,dp[i-1]);
            }
        }
        return dp[prices.size()-1];
    }
};

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(k == 0 || prices.empty())
            return 0;
        if(k > prices.size() / 2){
            int profit = 0;
            for(int i = 1; i<prices.size(); ++i)
                profit += max(prices[i] - prices[i-1],0);
            return profit;
        }
        
        vector<int>sell(k);
        vector<int>buy(k,numeric_limits<int>::max());
        for(auto price: prices){
            for(int i = 0; i<k; ++i){
                if(i == 0){
                    buy[0] = min(buy[0], price);
                }
                else {
                    buy[i] = min(buy[i], price - sell[i-1]);
                }
                sell[i] = max(sell[i], price - buy[i]);
            }
        }
        return sell.back();
    }
};

//not a good solution but it works
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.size()==0) return 0;
        vector<int>dp(prices.size(),0);
        
        for(int n = 1; n<=k && n<prices.size(); n++){
            int tempmax = -prices[0];
            for(int i = 1; i<prices.size();i++){
                int lastprof = dp[i];
                dp[i] = max(tempmax + prices[i], dp[i-1]);
                tempmax = max(tempmax, lastprof-prices[i]);
            }
        }
        return dp[prices.size()-1];
    }
};