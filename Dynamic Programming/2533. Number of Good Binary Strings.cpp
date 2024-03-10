class Solution {
public:
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {
        vector<long>dp(maxLength+1);
        long res = 0;
        int mod = 1e9 + 7;
        dp[oneGroup] = 1;
        dp[zeroGroup] += 1; //one and zero could be the same group
        for(int i = 1; i<=maxLength; ++i){
            if(i > oneGroup){
                dp[i] = (dp[i] + dp[i-oneGroup]) % mod;
            } 
            if (i > zeroGroup){
                dp[i] = (dp[i] + dp[i-zeroGroup])% mod;
            }
            if (i >= minLength){
                res = (res + dp[i] ) % mod;
            }
            //cout<<i<<" dp[i] "<<dp[i]<<endl;
        }
        return res;
    }
};


