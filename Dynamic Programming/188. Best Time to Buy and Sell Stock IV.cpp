/*


Think Process:
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/306282/Different-DP-Python-solutions-with-thinking-process


*/

//2025
// profit inherit来自于 同一次交易的上一个 index
// cost 中的profit 来自于上一次交易的 同一个 index
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int>profit(n);
        for(int a = 0; a < k ; ++ a){
            int cost = prices[0];
            for(int i = 1; i < n; ++i){
                if(a > 0) cost = min(cost, prices[i] - profit[i]);
                //不可以是 cost = min(cost, prices[i] - profit[i-1]);
                //profit[i-1] 可能是同样的a, 刚update过的profit, 就相当于带着刚计算过profit[i-1] 再次买入 而不是用上一轮的
                else cost = min(cost, prices[i]); 
                profit[i] = max(profit[i-1], prices[i] - cost);
            }
        }
        return profit[n-1];
    }
};

/*

               [3,  3,  5,  0,  0,   3,  1,  4]
第一轮  cost =   3   3,  3,  0 , 0,   0,  0,  0
      profit=   0,  0,  2,  2,  2,   3,  3,  4 

第二轮  cost =   3   3,  3, -2, -2, -2, -2,  -2
      profit=   0,  0,  2,  2,  2,   5,  5,  6     

*/


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int>profit(n);
        for(int p = 0; p < k; ++p){
            int cost = prices[0];
            for(int i = 1; i < n; ++i){
                cost = min(cost, prices[i]-profit[i]); //当 p == 0, profit[i] = 0
                profit[i] = max(profit[i-1], prices[i]-cost);
            }
        }
        return profit.back();
    }
};

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int>profit(n);
        for(int p = 0; p < k; ++p){
            int cost = prices[0];
            int tmp = profit[0];
            for(int i = 1; i < n; ++i){
                cost = min(cost, prices[i]-tmp); //prices[i] - profit[i-1]
                tmp = profit[i];
                profit[i] = max(profit[i-1], prices[i]-cost);
            }
        }
        return profit.back();
    }
};

//2025
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int>cost(k, numeric_limits<int>::max());
        vector<int>profit(k);
        for(int i = 0; i < prices.size(); ++i){
            for(int j = 0; j < k; ++j){
                if ( j == 0) {
                    cost[j] = min(cost[j], prices[i]);
                } else {
                    cost[j] = min(cost[j], prices[i] - profit[j-1]);
                }
                profit[j] = max(profit[j], prices[i] - cost[j]);
            }
        }
        return profit[k-1];
    }
};


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


/*

Key point: 
1. 把小的trade 看能不能combine 成大的trade, 列出所有trade的profit, 然后sort and calculate result 
2. profit(v1, p2) + profit(v2, p1) = profit(v1, p1) + profit(v2, p2)： index : v1 < p1 < v2 < p2
    k = 1, return profit (v1, p2)
    k = 2, return profit (v1, p2) + profit (v2, p1)

e.g. 1: 
[6,10,7,11],
两个trade pair [6,10],  [7,11] 因为 11 > 10, update profit = [3(10-7), 5(11-6)], 
如果 k = 1,  result = 5,  如果 k = 2, result = 8

e.g. 2:
[6,8, 3,7],  pair: [6,8], [3,8]
因为 3 < 6,   so profit = [2, 5]
如果k = 1, result = 5, 如果k = 2, result = 7


https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54145/O(n)-time-8ms-Accepted-Solution-with-Detailed-Explanation-(C%2B%2B)

We use the term "valley" to denote a local minimum index of prices, and the term "peak" to denote a local maximum index of prices. 
Let (v1, p1) and (v2, p2) denote two successive valley-peak pairs of the prices, respectively. Consider the two cases:

v1 < p1 < v2 < p2

  Case 1: prices[v1] <= prices[v2] and prices[p1] <= prices[p2]. 
    In this case, if we can conduct one transaction, we will use (v1, p2). 
    If we can conduct two transactions, we will use (v1, p1) and (v2, p2). 
    Equivalently, we can consider (v1, p2) as one transaction opportunity, and (v2, p1) as another transaction opportunity. 
    The key idea is that these two original valley-peak pairs provide two transaction opportunities: (v1, p2) and (v2, p1).

  Case 2: prices[v1] >= prices[v2] or prices[p1] >= prices[p2]. 
    In this case, if we can conduct one transaction, we will use either (v1, p1) or (v2, p2). 
    If we can conduct two transactions, we will use both (v1, p1) and (v2, p2). 
    That is, these two valley-peak pairs provides two transaction opportunities: (v1, p1) and (v2, p2).

The algorithm consists of two steps:

Step 1: Find all transaction opportunities and record their profits. 
     We use a stack vps to store the valley-peak pairs of the stock prices, 
     wherein the valley value is sorted in ascending order. (The valley value at the top of the stack is the largest.) 
     The profit of all transaction opportunities are recorded in the vector profits. The time complexity of this step is O(n).

Step 2: Find the k most profitable transaction opportunities. 
    The maximum profit we can get is the summation of the k opportunity. The time complexity of this step is O(n), too.

Overall complexity:

Time: O(n)

Space: worse-case O(n)

 */

/*
the key point is: profit(v1, p2) + profit(v2, p1) = profit(v1, p1) + profit(v2, p2)
 */

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {

        // Step 1: Find out all profit opportunities            
        vector<int> profits;
        stack<pair<int, int>> vps; // valley-peak pairs
        
        int v;
        int p = -1;
        for (;;) {
            // find next valley-peak pair
            for (v = p+1; (v+1 < prices.size()) && (prices[v] >= prices[v+1]); ++v);
             //prices[v] >= prices[v+1] 不能成为买点, 比如 6，5  6>5， 不会在6买入
            for (p = v  ; (p+1 < prices.size()) && (prices[p] <= prices[p+1]); ++p);
            //prices[p] <= prices[p+1]: 不能成为卖点, 比如 7, 8,  7 < 8, 不会在7卖出
            
            if (v == p) { // v==p means that both v and p reach the end of the array
                break;
            }
            
            // Consider two transactions (v1, p1) (back of the stack) and (v2, p2) (the new-found).
            // If prices[v1] >= prices[v2], 
            // it is meaningless to combine the two transactions.
            // Save of profit of (v1, p1), and pop it out of the record.
            // 比如  vps;{6,10}, {7,8},  v : 3, p: 6,  save 8-6 = 2 as profit and 8-7 = 1 as profit  
            while ((!vps.empty()) && (prices[v] <= prices[vps.top().first])) {
                profits.push_back(prices[vps.top().second] - prices[vps.top().first]);
                vps.pop();
            }
            
            // If prices[v1]<prices[v2] and prices[p1]<prices[p2], 
            // then it is meaningful to combine the two transactions
            // update (v1, p1) to (v1, p2), and save the profit of (v2, p1)
            //profit(v1, p2) + profit(v2, p1) = profit(v1, p1) + profit(v2, p2)
            //比如 vps: {6,10}, v: p = {7,11}, save 10 - 7 =  3 as profit 
            while ((!vps.empty()) && (prices[p] >= prices[vps.top().second])) {
                profits.push_back(prices[vps.top().second] - prices[v]);
                v = vps.top().first;
                vps.pop();
            }
            
            // save the new-found valley-peak pair
            vps.emplace(v, p);
        }
        
        // save all remaining profits
        while (!vps.empty()) {
            profits.push_back(prices[vps.top().second] - prices[vps.top().first]);
            vps.pop();
        }
        
        // Step 2: Calculate the k highest profits
        int ret;
        if (profits.size() <= k) {
            ret = accumulate(profits.begin(), profits.end(), 0);
        } else {
            nth_element(profits.begin(), profits.end() - k, profits.end());
            ret = accumulate(profits.end() - k, profits.end(), 0);
        }
        return ret;
    }
};