class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<long>dp(high+1);
        dp[zero] =  1;
        dp[one] += 1;
        int mod =  1e9 + 7;
        long res = 0;
        for(int i = min(zero, one); i<=high; ++i){
            if( i >= zero){
                dp[i] = (dp[i] + dp[i-zero]) % mod;
            } 
            if (i >= one){
                dp[i] = (dp[i] + dp[i-one]) % mod;
            }
            if (i >= low){
                res = (res + dp[i]) % mod;
            }
        }
        return res;
    }
};


class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1);
        dp[0] = 1;
        int res = 0, mod = 1e9 + 7;
        for (int i = 1; i <= high; ++i) {
            if (i >= zero) dp[i] = (dp[i] + dp[i - zero]) % mod;
            if (i >= one) dp[i] = (dp[i] + dp[i - one]) % mod;
            if (i >= low) res = (res + dp[i]) % mod;
        }
        return res;
    }
};