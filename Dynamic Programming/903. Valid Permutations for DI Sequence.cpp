

/*
DP[i][j] 表示 当combination 有i+1个数，其中第i+1个数是，所有可选择中(未被之前i个数选择的)第j+1小的

分析图见 https://leetcode.com/problems/valid-permutations-for-di-sequence/discuss/168278/C%2B%2BJavaPython-DP-Solution-O(N2)


若 S[i] = "I"，  那么 dp[i][j] = sum(dp[i][k] for k in [0,j])  :  i - 1 选择为k 后，那么可以选择的pool 少了一位，当选择至少为第k小时，就是增加
若 s[i] = "D",  那么 dp[i][j] = sum(dp[i][k] for k in [j+1, n-i])


*/


class Solution {
public:
    int numPermsDISequence(string S) {
        int n  = S.size()+1;
        vector<vector<long>>dp(n, vector<long>(n));
        int mod = pow(10,9)+7;
        for(int i = 0; i<n; ++i) dp[0][i] = 1;
        
        for(int i = 1; i<n; ++i){
            for(int j = 0; j<n-i; ++j){
                if(S[i-1] == 'D')
                {
                    for(int k = j+1; k<n-i+1; ++k){
                        dp[i][j] = (dp[i][j] + dp[i-1][k]) % mod;
                    }
                }
                else 
                    for(int k = j; k>=0; --k)
                        dp[i][j] = (dp[i][j] + dp[i-1][k]) % mod;
            }
        }
        return dp[n-1][0];
    }
};


//O(n^2) complexity 
class Solution {
public:
    int numPermsDISequence(string S) {
        int n = S.length(), mod = 1e9 + 7;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for (int j = 0; j <= n; j++) dp[0][j] = 1;
        for (int i = 0; i < n; i++)
            if (S[i] == 'I')
                for (int j = 0, cur = 0; j < n - i; j++)
                    dp[i + 1][j] = cur = (cur + dp[i][j]) % mod;
            else
                for (int j = n - i - 1, cur = 0; j >= 0; j--)
                    dp[i + 1][j] = cur = (cur + dp[i][j + 1]) % mod;
        return dp[n][0];
    }
};



//O(N) space
class Solution {
public:
    int numPermsDISequence(string S) {
        int n = S.length(), mod = 1e9 + 7;
        vector<int> dp(n + 1, 1), dp2(n);
        for (int i = 0; i < n; dp = dp2, i++) {
            if (S[i] == 'I')
                for (int j = 0, cur = 0; j < n - i; j++)
                    dp2[j] = cur = (cur + dp[j]) % mod;
            else
                for (int j = n - i - 1, cur = 0; j >= 0; j--)
                    dp2[j] = cur = (cur + dp[j + 1]) % mod;
        }
        return dp[0];
    }
};


/*
Method 2  Divide and Conquer
Much SLower 

比如: s='IIDD', we can only insert 4 between I and D. 
We break the remained numbers 0, 1, 2, 3 into two groups both with the size of 2. 
We have C(4, 2) possible combinations. Then helper("IIDD") = helper("I") * helper("D") * C(4, 2).
    
比如
    I  I 3  D  D
  0   1      2   0

如果有多个 ID   比如  IIDIDI, 5 可以在第一个I 和 D之间，也可以在第二个 I 和 D之间
                I I D I D I
                   5   5
 */

class Solution {
public:
    unordered_map<int, unordered_map<int,int>>nCkMemo;
    int M = pow(10,9)+7;
    
    int numPermsDISequence(string S) {
        unordered_map<string, long>dp;
        
        return topDown(dp, S);
    }
    
    long topDown(unordered_map<string, long>&dp, string S){
        if(S.size() == 0)
            return 1;
        if(dp.count(S))
            return dp[S];
        long res = 0;
        if(S[0] == 'D'){
            res = topDown(dp, S.substr(1));
        }
        if(S.back() == 'I'){
            res = (res + topDown(dp, S.substr(0,S.size()-1)))%M;
        }
        for(int i = 1; i<S.size(); ++i)
        {
            if(S[i] == 'D' && S[i-1] == 'I')
            {
                long left = 1, right = 1;
                if(i>1)
                    left = topDown(dp, S.substr(0,i-1));
                if(i<S.size())
                    right = topDown(dp, S.substr(i+1));
                res = (res + (left * right) % M*nCk(S.size(),i)%M)%M;
            }
        }
        return dp[S] = res;
    }
    
    int nCk(int n, int k){
        if (k == 0 || k == n) {
            return 1;
        }
        if (nCkMemo[n][k] == 0) {
            nCkMemo[n][k] = (nCk(n - 1, k) + nCk(n - 1, k - 1)) % M;
        }
        return nCkMemo[n][k];
    }
};


//Bottom-up
/*
DP[i][j] 表示从 S[i:j] 可以有几种permutation 选择
 */
class Solution {
public:
    unordered_map<int, unordered_map<int,int>>nCkMemo;
    int M = pow(10,9)+7;
    
    int numPermsDISequence(string S) {
        int n = S.size();
        vector<vector<long>>dp(n, vector<long>(n));
        for(int i = 0; i<n; ++i)
            dp[i][i] = 1;
        for(int len = 1; len <n; ++len){
            for(int l = 0; l<n-len; ++l){
                int r = l + len;
                if(S[l] == 'D')
                    dp[l][r] = (dp[l][r] + dp[l+1][r]) % M;
                if(S[r] == 'I')
                    dp[l][r] = (dp[l][r] + dp[l][r-1]) % M;
                for(int k = l+1; k<=r;++k){
                    if(S[k-1] == 'I' && S[k] == 'D'){
                        long left = 1, right = 1;
                        if(k>l+1)
                            left = dp[l][k-2];
                        if(k<r)
                            right = dp[k+1][r];
                        dp[l][r] =  (dp[l][r] + (left * right)%M*nCk(len+1, k-l)%M)%M;
                    }
                }
            }
        }
        
        return dp[0][n-1];
    }
    
  
    int nCk(int n, int k){
        if (k == 0 || k == n) {
            return 1;
        }
        if (nCkMemo[n][k] == 0) {
            nCkMemo[n][k] = (nCk(n - 1, k) + nCk(n - 1, k - 1)) % M;
        }
        return nCkMemo[n][k];
    }
};


/**
 O(N^3) dp 

 dp[i][j] 表示 permutation number 0, 1, ... i+1 中end with 第j+1个小的 有多少种组合 ,
 
  比如 dp[2][2], 表示 有3个数permutation, 第三个数是最大的, 比如 1 2 3 （3最大的), 1，2，5 （5也是最大的)
 
s.charAt(i - 1) == 'I': In this case, dp[i][j] = sum(dp[i - 1][0], dp[i - 1][1], ... , dp[i - 1][j - 1]).
s.charAt(i - 1) == 'D': In this case, dp[i][j] = sum(dp[i - 1][j], dp[i - 1][j + 1], ... , dp[i - 1][i - 1]).
 
 */


class Solution {
public:
    
    int numPermsDISequence(string S) {
        int n = S.size();
        int M = pow(10,9)+7;
        vector<vector<long>>dp(n+1, vector<long>(n+1));
        dp[0][0] = 1;
        for(int i = 1; i <=n; ++i){
            for(int j = 0; j<=i; ++j){
                if(S[i-1] == 'I'){
                    for(int k = 0;  k<j; ++k)
                        dp[i][j] = (dp[i][j] + dp[i-1][k])%M;
                }
                else{
                    for(int k = j;  k<=i; ++k)
                        dp[i][j] = (dp[i][j] + dp[i-1][k])%M;
                }
            }
        }
        long res = 0;
        for(int i = 0; i<=n; ++i)
            res = (res + dp[n][i])%M;
        return res;
    }
};


/**
 O(N^2)

s.charAt(i - 1) == 'I': In this case, dp[i][j] = sum[i - 1][j - 1].
s.charAt(i - 1) == 'D': In this case, dp[i][j] = sum[i - 1][i - 1] - sum[i - 1][j - 1].

因为dp[i][i] 表示 所有 i个数的combination,
 */

class Solution {
public:
    
    int numPermsDISequence(string S) {
        int n = S.size();
        int M = pow(10,9)+7;
        vector<vector<long>>dp(n+1, vector<long>(n+1));
        dp[0][0] = 1;
        for(int i = 1; i <=n; ++i){
            for(int j = 0; j<=i; ++j){
                dp[i][j] = j == 0 ? 0: dp[i][j-1]; //因为dp[i][i] 表示 所有 i个数的combination, 所以是culmulative
                if(S[i-1] == 'I'){
                    dp[i][j] += (j == 0 ? 0: dp[i-1][j-1]);
                }
                else{
                    dp[i][j] += (dp[i-1][i-1] - (j==0? 0: dp[i-1][j-1]));
                    if(dp[i][j] < 0)
                        dp[i][j] += M;  //因为有可能 dp[i-1][i-1] - dp[i-1][j-1] 是一个很负的数
                }
                dp[i][j] = dp[i][j] % M;
            }
        }
        return dp[n][n];
    }
};