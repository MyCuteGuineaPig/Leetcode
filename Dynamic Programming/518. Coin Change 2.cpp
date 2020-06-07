class Solution {
public:
    int change(int amount, vector<int>& coins) {
        unordered_map<int,unordered_map<int,int>>dp;
        sort(coins.begin(), coins.end());
        return f(dp, coins, amount, 0);
    }
    
    int f( unordered_map<int,unordered_map<int,int>>&dp, const vector<int>& coins, int cur, int pos){
        if(cur == 0)
            return dp[pos][cur] = 1;
        if(dp.count(pos) && dp[pos].count(cur))
            return dp[pos][cur];
        for(int i = pos; i < coins.size(); i++){
            if(coins[i]<=cur){
                dp[pos][cur] += f(dp, coins, cur-coins[i], i);
            }
            else 
                break;
        }
        return dp[pos][cur];
        
    }
};

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        unordered_map<int,unordered_map<int,int>>dp;
        sort(coins.begin(), coins.end());
        return f(dp, coins, amount, 0);
    }
    
    int f( unordered_map<int,unordered_map<int,int>>&dp, const vector<int>& coins, int cur, int pos){
        if(cur == 0)
            return dp[pos][cur] = 1;
        if(cur < 0 || pos == coins.size())
            return 0;
        if(dp.count(pos) && dp[pos].count(cur))
            return dp[pos][cur];
        
        int use = f(dp, coins, cur - coins[pos], pos);
        int jump = f(dp, coins, cur, pos + 1);
        return dp[pos][cur] = (jump + use);
        
    }
};
/**
 dp[i - 1][j]: 完全不用当前硬币组成j有多少种组合
dp[i][j - coins[i - 1]] :使用至少一个当前硬币（与上面一条是互斥事件）组成组成j有多少组合

dp[i][j] : 用使用前i个硬币组成j

why the outer loop is the coins, not the amount. 

The reason behind that is that as you mentioned, the problem is to find the total number of combinations, not the permutations. 
If the outer loop is the amount, then the same combination will be counted multiple times because they can come in in different orders. 
By letting the coins to be the outer loops, one assures that for any valid combination, 
the order of each coin will always be the same as their order in coins, so there can be no duplicates.
 */

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 0)
            return 1;
        if(coins.empty()) 
            return 0;
        vector<vector<int>>dp(coins.size(), vector<int>(amount+1, 0));
       
        for(int i = 0; i<coins.size(); ++i){
            dp[i][0] = 1;
            for(int j = 1; j<=amount; ++j)
            {
                dp[i][j] = (i == 0 ? 0 : dp[i-1][j]) + (coins[i] <= j ? dp[i][j-coins[i]]: 0);
            }
        }
        
        return dp[coins.size()-1][amount];
    }
};


class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 0)
            return 1;
        if(coins.empty()) 
            return 0;
        vector<int>dp(amount+1, 0);
        dp[0] = 1;
        
        for(int i = 0; i<coins.size(); ++i){
            for(int j = 1; j<=amount; ++j)
            {
                dp[j] = dp[j] + (coins[i] <= j ? dp[j-coins[i]]: 0);
            }
        }
        
        return dp[amount];
    }
};