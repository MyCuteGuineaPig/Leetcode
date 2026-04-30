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


class Solution {
public:
    int countPalindromes(string s) {
        int n  = s.size();

        vector<int>cnt(10);
        vector<vector<long>> prefix(10, vector<long>(10));
        vector<vector<long>> suffix(10, vector<long>(10));
        vector<vector<vector<long>>> suffix_at(n, vector<vector<long>>(10, vector<long>(10)));

        for(int i = n-1; i >= 0; --i) {
            int c = s[i] - '0';
            for(int j = 0; j < 10; ++j) {
                suffix[c][j] += cnt[j];
            }
            for(int j = 0; j < 10 ; ++j)
                for(int k = 0; k < 10; ++k)
                    suffix_at[i][j][k] = suffix[j][k];
            cnt[c]++;
        }

        cnt.assign(10, 0);
        long long res = 0;
        long long mod = 1e9 + 7;
        for(int i = 0; i < n - 2; ++i) {
            int c = s[i] - '0';
            if (i > 1) {
                for(int j = 0; j < 10; ++j)
                    for(int k = 0; k < 10; ++k)
                        res = (res + prefix[j][k]*suffix_at[i+1][j][k]) % mod;
            }
            
            for(int j = 0; j < 10; ++j) 
                prefix[c][j] += cnt[j];


            cnt[c]++;
        }
        return res;
    }
};






class Solution {
public:
    int countPalindromes(string s) {
        int n = s.size();
        long long mod = 1e9 + 7, res = 0;
        
        // pre[i][j] = count of prefix sequence "ij"
        // suf[i][j] = count of suffix sequence "ij"
        long long pre[10][10] = {}, suf[10][10] = {};
        long long pre_cnt[10] = {}, suf_cnt[10] = {};
        
        // Suffix data for the entire string
        vector<vector<long long>> suf_at(n, vector<long long>(100, 0));
        
        // Build suffix pair counts from right to left
        for (int i = n - 1; i >= 0; --i) {
            int d = s[i] - '0';
            for (int j = 0; j < 10; ++j) {
                suf[d][j] = (suf[d][j] + suf_cnt[j]); // --> only current digit matters
            }
            suf_cnt[d]++;
            for (int j = 0; j < 100; ++j) {
                suf_at[i][j] = suf[j / 10][j % 10];
            }
        }

        // Iterate through the string to find the center 'i' of "ab i ba"
        for (int i = 0; i < n; ++i) {
            int d = s[i] - '0';
            
            //  Count palindromes centered at i
            // We need prefix "jk" and suffix "kj"
            if (i > 1 && i < n - 2) {
                for (int j = 0; j < 10; ++j) {
                    for (int k = 0; k < 10; ++k) {
                        res = (res + pre[j][k] * suf_at[i + 1][k * 10 + j]) % mod;
                    }
                }
            }

            // 3. Add current digit to prefix counts
            for (int j = 0; j < 10; ++j) {
                pre[j][d] = (pre[j][d] + pre_cnt[j]);
            }
            pre_cnt[d]++;
        }

        return res;
    }
};