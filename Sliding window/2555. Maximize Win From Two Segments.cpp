class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int res=0;
        int l = 0;
        int n = prizePositions.size(); 
        vector<int>dp(n+1);
        for (int i  = 0; i < n; ++i) {
            while (prizePositions[l] < prizePositions[i] - k) 
                ++l;
            dp[i+1] = max(dp[i], i - l + 1);
            res = max(res, i-l+1 + dp[l]);
            /*
            不能用max(res,dp[i] + dp[l]); 可能dp[i] 和 dp[l] 重叠   
            i - l + 1 是以i结尾的窗口l开始的最大值， dp[l]是以l-1结尾的最大值，两者不重叠
            
             */
        }
        return res;
    }
};