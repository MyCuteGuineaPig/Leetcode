/*

pre[i][j][k] = number of subsequences "j k" in s[0...i]

比如 s = "103301"   

pre[1][1][0] = 1 表示 在index = 1, 10 这个subsequence 出现了1次

suffix[i][j][k] = number of subsequences "j k" in s[i...n-1]    

suffix[4][0][1] = 1 表示 在index = 4, 01 这个subsequence 出现了1次

 */

class Solution {
public:
    int countPalindromes(string s) {
        int n  = s.size();
        vector<vector<vector<long>>>pre(n, vector<vector<long>>(10, vector<long>(10)));
        vector<vector<vector<long>>>suf(n, vector<vector<long>>(10, vector<long>(10)));

        vector<int>cnt(10);

        for(int i = 0; i < n; ++i) {
            int c = s[i] - '0';
            if (i > 0) {
                for(int j = 0; j < 10; ++j) {
                    for(int k = 0; k < 10; ++k) {
                        pre[i][j][k] = pre[i-1][j][k];
                        if (c == k) {
                            pre[i][j][k] += cnt[j];
                        }
                    }
                }
            }
            cnt[c]++;
        }

        cnt.assign(10, 0); 
        for(int i = n-1; i >= 0; --i) {
            int c = s[i] - '0';
            if (i < n -1) {
                for(int j = 0; j < 10; ++j) {
                    for(int k = 0; k < 10; ++k) {
                        suf[i][j][k] = suf[i+1][j][k];
                        if (j == c) { // <--- important j == c, not c == k
                            suf[i][j][k] += cnt[k];
                        }
                    }
                }
            }
            cnt[c]++;
        }
        long long res = 0;
        long long mod = 1e9 + 7;
        for(int i = 2; i < n - 2; ++i){
            for(int j = 0; j < 10; ++j) {
                for(int k = 0; k < 10; ++k)
                    res = (res + pre[i-1][j][k]*suf[i+1][k][j]) % mod; //<-- important suf[i+1][k][j] not suf[i+1][j][k]
                    // 10 3 01    
            }
        }
        return res;
    }
};