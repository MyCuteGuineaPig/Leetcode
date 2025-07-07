class Solution {
public:
    int helper(int i, int k, vector<int>& nums, unordered_map<int, unordered_map<int,int>>&dp){
        if (i == nums.size()) return 0;
        if (k <= 0 ) return numeric_limits<int>::max();
        if (dp.count(i) && dp[i].count(k)) return dp[i][k];
        
        int n = nums.size();

        int xorr = 0;
        int res = numeric_limits<int>::max();
        for (int ind = i; ind < n && ind <= n-k ; ++ind){
            xorr ^= nums[ind];
            if (xorr < res) {
                res = min(res, max( xorr, helper(ind+1, k - 1, nums, dp)));
            }
        }
        return dp[i][k] = res;
    }

    int minXor(vector<int>& nums, int k) {
        
        unordered_map<int, unordered_map<int,int>>dp;
        return helper(0, k, nums, dp);
    }
};


class Solution {
public:
    int helper(int i, int k, vector<int>& nums, vector<vector<int>>&dp){
        if (i == nums.size()) return 0;
        if(k <= 0 ) return numeric_limits<int>::max();
        // 还有数没有分完
        if (dp[i][k]!=-1) return dp[i][k];
        
        int n = nums.size();

        int xorr = 0;
        int res = numeric_limits<int>::max();
        for (int ind = i; ind < n && ind <= n-k ; ++ind){
            //需要 ind <= n-k， 否则可能出现，前面数分太多，分不到k组的情况
            xorr ^= nums[ind];
            res = min(res, max( xorr, helper(ind+1, k - 1, nums, dp)));
        }
        return dp[i][k] = res;
    }

    int minXor(vector<int>& nums, int k) {
        vector<vector<int>>dp(nums.size(), vector<int>(k+1,-1));
        return helper(0, k, nums, dp);
    }
};


class Solution {
public:
    int minXor(vector<int>& nums, int k) {
        int n = nums.size();
        vector memo(k + 1, vector<int>(n, -1));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i == 0) {
                return j < 0 ? 0 : INT_MAX;
            }
            if (j < i - 1) {
                return INT_MAX;
            }
            if (memo[i][j] != -1) {
                return memo[i][j];
            }

            int res = INT_MAX;
            int s = 0;
            for (int l = j; l >= i - 1; l--) {
                s ^= nums[l];
                res = min(res, max(dfs(i - 1, l - 1), s));
            }
            return memo[i][j] = res;
        };
        return dfs(k, n - 1);
    }
};