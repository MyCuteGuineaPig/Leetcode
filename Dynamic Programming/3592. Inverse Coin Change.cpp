class Solution {
public:
    vector<int> findCoins(vector<int>& numWays) {
        int n = numWays.size(); 
        vector<int>dp(n+1);
        dp[0] = 1;
        for(int i = 0; i < n; ++i){
            dp[i+1] = numWays[i];
        }
        vector<int>res;
        for(int i = 1; i <= n; ++i){
            if(dp[i] > 1) return {};
            if(dp[i] == 0) continue;
            res.push_back(i);
            for(int j = n; j >= i; --j){
                dp[j] -= dp[j-i];
                if (dp[j] < 0) return {};
            }
        }
        return res;
    }
};

//or 
class Solution {
public:
    vector<int> findCoins(vector<int>& numWays) {
        int n = numWays.size();
        vector<int>dp(n+1); dp[0] = 1;
        for(int i = 0; i < n; ++i){
            dp[i+1] = numWays[i];
        }
        vector<int>res;
        for(int i = 1; i<=n ; ++i){
            if(dp[i] != 0 && dp[i]!= 1) {
                return {};
            }
            if (dp[i] == 0) continue;
            res.push_back(i);
            for(int j = n ; j >= i; --j){
                dp[j] -= dp[j-i];
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> findCoins(vector<int>& numWays) {
        int n = numWays.size(); 
        vector<int>dp(n+1);
        vector<int>res;
        dp[0] = 1;
        for(int i = 1; i <= n; ++i){
            if (dp[i] == numWays[i-1])
                continue;
            if (numWays[i-1] != dp[i]+1) {
                return {};
            }

            res.push_back(i);
            for (int j = i; j <=n; ++j){
                dp[j] += dp[j-i];
            }
        }
        return res;
    }
};