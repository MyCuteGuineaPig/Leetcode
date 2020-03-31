class Solution:
    def coinChange(self, coins, amount):
        dp = [10000000000 for _ in range(amount+1)]
        dp[0] = 0
        coins.sort()
        for i in range(1, amount+1):
            for cc in coins: 
                if cc > i: break
                dp[i] = min(dp[i], dp[i-cc]+1)
        return dp[amount] if dp[amount]!=10000000000 else -1

class Solution:
    def coinChange(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        dp = [10000000000 for _ in range(amount+1)]
        dp[0] = 0
        coins.sort()
        for cc in coins:
            if cc > amount: break
            dp[cc] = 1
            for i in range(cc+1, amount+1):
                dp[i] = min(dp[i], dp[i-cc]+1)
        return dp[amount] if dp[amount]!=10000000000 else -1



#DFS

class Solution:
    def coinChange(self, coins, amount):
        MAX = float('inf')
        def dfs(count, beg, remaining, ans):
            if remaining == 0:
                ans[0] = min(ans[0], count)
                return 
            if remaining < 0: 
                return 
            for i in range(beg, len(coins)):
                if coins[i] <= remaining < (ans[0] - count)*coins[i]:
                    dfs(count+1,i, remaining - coins[i], ans)
        ans = [MAX]
        coins.sort(reverse = True)
        dfs(0, 0, amount,ans)
        return -1 if ans[0] == MAX else ans[0]




/**
C++
*/

DP, the below code is self-explained. 
```
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
```
 
DFS Solution. Sort coins at first. Then add constraint ```remaining >= coins[i] && remaining < (ans-count)*coins[i]``` to speed up. If remaining amount is less than minimum change* coins[i], no more need to do another DFS which just waste of time 
```

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
````


BFS: push current number in coins into a queue, then do another changes as well increase step by 1 and decide if the new number should be pushed into the queue. If we hit the amount, return the step. 
```

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
```