class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int firstMax = *max_element(nums1.begin(), nums1.end());
        int secondMax = *max_element(nums2.begin(), nums2.end());
        int firstMin =  *min_element(nums1.begin(), nums1.end());
        int secondMin = *min_element(nums2.begin(), nums2.end());
        
        if (firstMax < 0 && secondMin > 0) 
            return firstMax * secondMin;
        if (secondMax < 0 && firstMin > 0) 
            return secondMax * firstMin;

        int n = nums1.size(), m = nums2.size();
        vector<vector<long>> dp(n+1, vector<long>(m+1, numeric_limits<int>::min()));
        for(int i = 0; i <= n; ++i)
            dp[i][0] = 0; 
        for(int j = 0; j <= m; ++j)
            dp[0][j] = 0; 
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                int cur = nums1[i] * nums2[j];
                dp[i+1][j+1] = max({dp[i][j] + cur, dp[i+1][j], dp[i][j+1]});
            }
        }
        return dp[n][m];
    }
};


class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int firstMax = *max_element(nums1.begin(), nums1.end());
        int secondMax = *max_element(nums2.begin(), nums2.end());
        int firstMin =  *min_element(nums1.begin(), nums1.end());
        int secondMin = *min_element(nums2.begin(), nums2.end());
        
        if (firstMax < 0 && secondMin > 0) 
            return firstMax * secondMin;
        if (secondMax < 0 && firstMin > 0) 
            return secondMax * firstMin;

        int n = nums1.size(), m = nums2.size();
        vector<vector<long>> dp(n, vector<long>(m, numeric_limits<int>::min()));

        auto top = [&](this auto&& top, int i, int j) -> int {
            if(i == -1 || j == -1) {
                return 0;
            }
            if (dp[i][j] != numeric_limits<int>::min()) 
                return dp[i][j];
            return dp[i][j] = max({top(i-1, j-1) + nums1[i]*nums2[j], top(i-1, j), top(i, j-1)});
        };
        return top(n-1, m-1);
    }
};