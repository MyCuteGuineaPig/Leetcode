/*
dp
*/

// Bottom-up
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

//2025 
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        vector<int>dp(amount+1, amount + 2);
        dp[0] = 0;
        auto helper = [&](this auto& helper, int cur){
            if(cur == 0 || dp[cur] < amount + 2) {
                return dp[cur];
            }
            for(auto& coin: coins) {
                if (cur - coin < 0) break;
            
                int tmp = helper(cur - coin);
                if (tmp != -1)
                    dp[cur] = min(dp[cur], tmp + 1);
            }
            return dp[cur] = (dp[cur] >= amount + 2 ? -1: dp[cur]);
        };
        helper(amount);
        return dp[amount] >= amount + 2 ? -1: dp[amount];
    }
};


//2025 bottom up
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        vector<int>dp(amount+1, amount + 2);
        dp[0] = 0;
        for(int i = coins[0]; i <= amount; ++i){
            for(auto coin: coins){
                if (coin > i) break;
                if (dp[i - coin] >= amount + 2) continue;
                dp[i] = min(dp[i], dp[i-coin]+1);
            }
        }
        return dp[amount] >= amount + 2 ? -1: dp[amount];
    }
};


// Bottom-up
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


// Top-Down
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amount+1,numeric_limits<int>::max());
        return topDown(coins, dp, amount);
    }
    
    int topDown(const vector<int>&coins,vector<int>&dp, int amount){
        if(amount == 0)
            return 0;
        if(dp[amount]!= numeric_limits<int>::max())
            return dp[amount];
        int cur = numeric_limits<int>::max();
        for(auto c: coins)
            if(amount - c>=0){
                int res = topDown(coins, dp, amount-c); 
                if(res!=-1)
                    cur = min(cur, 1+res);
            }
        return dp[amount] = (cur == numeric_limits<int>::max()?-1: cur);
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

