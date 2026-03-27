class Solution {
public:
    int minOperations(int n) {
        int res = 0;
        while (n > 0) {
            if ((n& 3) == 3) {
                res ++;
                n++;
            } else {
                res += n & 1; 
                n = n >> 1;
            }
        }
        return res;
    }
};


class Solution {
public:
    int minOperations(int n) {
        int res = 0;
        unordered_map<int, int > dp;
        auto helper = [&](this auto&& helper, int n) {
            if (n == 0) return 0;
            if (dp.count(n)) return dp[n];
            if ( (n & (n-1)) == 0) return dp[n] = 1;

            int p = 1; 
            while (p < n) p = p << 1;

            int add = 1 + helper(p - n);
            int minus = 1 + helper(n - (p >> 1));
            return dp[n] = min(add, minus);
        };
        return helper(n);
    }
};