/*

322. Coin Change

You are given coins of different denominations and a total amount of money amount. 
Write a function to compute the fewest number of coins that you need to make up that amount. 
If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.


*/

/*
dp
*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        vector<long>dp(amount+1,INT_MAX);
        dp[0] = 0;
        for(auto one: coins){
            if(one>amount) break;
            dp[one] = 1;
            for(long i = one+1; i<=amount; i++)
                dp[i] = min(dp[i],dp[i-one]+1);
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        vector<int>dp(amount+1,100000000);
        dp[0] = 0;
        for(auto one: coins){
            if(one>amount) break;
            dp[one] = 1;
            for(int i = one+1; i<=amount; i++)
                dp[i] = min(dp[i],dp[i-one]+1);
        }
        return dp[amount] == 100000000 ? -1 : dp[amount];
    }
};

/**BFS**/
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amount+1,INT_MAX);
        if(amount == 0) return 0;
        queue<int>q;
        for(auto i: coins){
            if(i==amount) return 1;
            if(i>amount) continue;
            dp[i] = 1;
            q.push(i);
        }
        int step = 1;
        while(q.size()){
            step++;
            int size = q.size();
            for(int i = 0; i<size; i++){
                int top = q.front();
                q.pop();
                for(auto i: coins){
                    if(i+top == amount)
                        return step;
                    if(i+top < amount && dp[i+top] == INT_MAX){
                       dp[i+top] = step;
                       q.push(i+top);
                    }
                }
            }
        }
        return -1;
    }
};

/*
DFS
*/
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.rbegin(),coins.rend());
        long long ans = INT_MAX;
        dfs(coins, 0, amount, 0, ans);
        return ans == INT_MAX ? -1: ans;
    }

    void dfs(vector<int>& coins, int beg, long long remaining, long long count, long long& ans){
        if(remaining == 0){
            ans = min(ans, count);
            return;
        }
        for(int i = beg; i<coins.size(); i++)
            if (remaining >= coins[i] && remaining < (ans-count)*coins[i])
                dfs(coins, i, remaining -coins[i], count+1, ans);
    }
};
