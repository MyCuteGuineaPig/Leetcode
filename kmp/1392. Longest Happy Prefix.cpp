/**
 * Rolling Hash
 * 
 */

class Solution {
public:
    string longestPrefix(string &s) {
        long h1 = 0, h2 = 0, mul = 1, len = 0, mod = 1000000007;
        for (int i = 0, j = s.length() - 1; j > 0; ++i, --j) {
            int first = s[i] - 'a', last = s[j] - 'a';
            h1 = (h1 * 26 + first) % mod;
            h2 = (h2 + mul * last) % mod;
            mul = mul * 26 % mod;
            if (h1 == h2) { // Collision-Aware Incremental Hash
            if (s.compare(0, i + 1 - len, s, j, s.size() - j - len) == 0 &&
               s.compare(len, i + 1 - len, s, j + len, s.size() - j - len) == 0)
                len = i + 1;
            }
        }
        return s.substr(0, len);
    }
};

/**
 * KMP
 */

class Solution {
public:
    string longestPrefix(string &s) {
        vector<int> dp(s.size());
        int j = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == s[j])
                dp[i] = ++j;
            else if (j > 0) {
                j = dp[j - 1];
                --i;
            }
        }
        return s.substr(0, j);
    }
};