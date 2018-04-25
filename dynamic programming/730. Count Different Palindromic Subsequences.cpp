/*
730. Count Different Palindromic Subsequences

Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.

A subsequence of a string S is obtained by deleting 0 or more characters from S.

A sequence is palindromic if it is equal to the sequence reversed.

Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

Example 1:
Input: 
S = 'bccb'
Output: 6
Explanation: 
The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
Example 2:
Input: 
S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
Output: 104860361
Explanation: 
There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
Note:

The length of S will be in the range [1, 1000].
Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.

*/


/*
Let dp[len][i][x] be the number of distinct palindromes of the subtring starting at i of length len, where the first (and last) character is x. 
The DP formula is simple :

If s[i] != x, then dp[len][i][x] = dp[len-1][i+1][x] (ignoring the first character in this window)
If s[i+len-1] != x then dp[len][i][x] = dp[len-1][i][x] (ignoring the last character in this window)
If both the first and last characters are x, then we need to count the number of distinct palindromes in the sub-window from i+1 to i + len -2.
 Need to be careful with how we count empty string.
Since we only need to subproblems of length len-1, len-2, we only need to remember the solutions for the subproblems of length len, len-1, len-2.
 This is needed to pass the max test case.

*/

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        const long long M = 1e9 + 7;
        int n = S.size();
        long long dp[3][n][4];
        for(int len = 0; len<n; len++){
            for(int i = 0; i+len<n;i++){
                for(int x = 0; x<4; x++){
                    int j = i+len;
                    dp[2][i][x] = 0;
                    char c = 'a'+x;
                    if(len == 0) dp[2][i][x] = S[i] == c;
                    else{
                        if(S[i]!=c) dp[2][i][x] = dp[1][i+1][x]; //len>=1 i+1<n
                        else if(S[j]!=c) dp[2][i][x] = dp[1][i][x];
                        else{
                            dp[2][i][x] = 2; // 比如bccb, bb是2个Palindromic，b && bb
                            if(len>=2) for(int y = 0; y<4; y++)
                                dp[2][i][x] = (dp[2][i][x]+dp[0][i+1][y])%M;
                        }
                    } 
                }   
            }
            for(int i = 0; i<2;i++) for(int j = 0; j<n; j++) for(int x = 0; x<4; x++)
                dp[i][j][x] = dp[i+1][j][x];
            
        }
        return accumulate(dp[2][0],dp[2][0]+4,0,[&](auto a, auto b){return (a+b)%M;});
    }
};






class Solution {
public:
    int countPalindromicSubsequences(string s) {
        int md = 1000000007;
        int n = s.size();
        int dp[3][n][4];
        for (int len = 1; len <=n; ++len) {
            for (int i = 0; i + len <=n; ++i) for (int x = 0; x < 4; ++x)  {
                int &ans = dp[2][i][x];
                ans = 0;
                int j = i + len - 1;
                char c = 'a' + x;
                if (len == 1) ans = s[i] == c;
                else {
                    if (s[i] != c) ans = dp[1][i+1][x];
                    else if (s[j] != c) ans = dp[1][i][x];
                    else {
                        ans = 2;
                        if (len > 2) for (int y = 0; y < 4;++y) {
                            ans += dp[0][i+1][y];
                            ans %=md;
                        }
                    }
                }
            }
            for (int i=0;i<2;++i) {
                //cout<<" len "<<len<<" i+1 "<<i+1<<endl;
                for (int j = 0; j < n; ++j){
                    for (int x=0; x < 4;++x){
                         dp[i][j][x] = dp[i+1][j][x];
                         //cout<<dp[i+1][j][x]<<" ";
                    }
                    //cout<<endl;
                }
            }
            //cout<<endl;
            
            for (int i=0;i<3;++i) {
                cout<<" len "<<len<<" i "<<i<<endl;
                for (int j = 0; j < n; ++j){
                    for (int x=0; x < 4;++x){
                         cout<<dp[i][j][x]<<" ";
                    }
                    cout<<endl;
                }
            }
            cout<<endl;
        }
        int ret = 0;
        for (int x = 0; x < 4;++x) ret = (ret + dp[2][0][x]) %md;
        return ret;
    }
};

/*
最快的
*/

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int m = S.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));
        for (int i = 0; i < m; i++) {
            dp[i][i] = 1;
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = i + 1; j < m; j++) {
                if (S[i] == S[j]) {
                    int left = i + 1, right = j - 1;
                    while (left <= right && S[left] != S[j]) {
                        left++;
                    }
                    while (left <= right && S[right] != S[j]) {
                        right--;
                    }
                    if (left > right) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 2; //所有的中间都乘以2，比如aba, b=1, aba = 2*1+2, 因为加上头和尾又可以组成新的回体字，2是因为头尾两个字可以单组，又可以一个单拿出来(aa,a)
                        //
                    } else if (left == right) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 1;//所有的中间都乘以2，比如aaa, b=1, aba = 2*1+1, 因为加上头和尾又可以组成新的回体字，1是因为头尾两个字可以单组，但不能单拿出来
                        //
                    } else {
                        dp[i][j] =
                            dp[i + 1][j - 1] * 2 - dp[left + 1][right - 1]; 
                            //比如"aabcaa"  //abca = 6， 把它乘以2，但是要减去里面的
                            //aabcaa, abca*2 = 12 - 2(bc) = 10, 减去原因因为外面的a(0)ca(5),a(0)ba(0), 和中间的a(1)ca(4),a(1)ba(4) 一样的。
                    }
                } else {
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
                }
                dp[i][j] = dp[i][j] < 0 ? dp[i][j] + 1000000007
                                        : dp[i][j] % 1000000007;
            }
        }
        return dp[0][m - 1];
    }
};

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        vector<vector<int>>dp(n,vector<int>(n));
        for(int i = n-1; i>=0; i--){
            dp[i][i] = 1;
            for(int j=i+1; j<n; j++){
                if(S[i] == S[j]){
                    int left = i+1, right = j-1;
                    while(left<=right && S[left]!=S[j]){
                        left++;
                    }
                    while(left<=right && S[right]!=S[j]){
                        right--;
                    }
                    if(left>right)
                        dp[i][j] = dp[i+1][j-1]*2 + 2;
                    else if(left == right)
                        dp[i][j] = dp[i+1][j-1]*2 + 1;
                    else
                        dp[i][j] = dp[i+1][j-1]*2 - dp[left+1][right-1];
                }
                else{
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
                }
                dp[i][j] = dp[i][j] < 0 ? dp[i][j] + 1000000007
                                        : dp[i][j] % 1000000007;
            }
        }
        return dp[0][n-1];
    }
};


class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int m = S.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));
        for (int i = 0; i < m; i++) {
            dp[i][i] = 1;
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = i + 1; j < m; j++) {
                if (S[i] == S[j]) {
                    int left = i + 1, right = j - 1;
                    cout<<" i "<<i<<"  j "<<j<<" left "<<left<<" right "<<right;
                    while (left <= right && S[left] != S[j]) {
                        left++;
                    }
                    while (left <= right && S[right] != S[j]) {
                        right--;
                    }
                    cout<<"  al "<<left<<" ar "<<right;
                    if (left > right) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
                        cout<<" condition1 "<<dp[i][j]<<" dp[i + 1][j - 1]  "<<dp[i + 1][j - 1]<<endl;
                    } else if (left == right) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
                        cout<<" condition2 "<<dp[i][j]<<" dp[i + 1][j - 1]  "<<dp[i + 1][j - 1]<<endl;
                    } else {
                        dp[i][j] =
                            dp[i + 1][j - 1] * 2 - dp[left + 1][right - 1];
                         cout<<" condition3 "<<dp[i][j]<<" dp[i + 1][j - 1]  "<<dp[i + 1][j - 1]<<"  dp[left + 1][right - 1] "<<dp[left + 1][right - 1]<<endl;
                    }
                } else {
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
                     cout<<" ouside i "<<i<<"  j "<<j<<" dp[i][j] "<<dp[i][j] <<" dp[i][j - 1]  "<<dp[i][j - 1]<<"  dp[i + 1][j]  "<< dp[i + 1][j] <<" dp[i + 1][j - 1]  "<<dp[i + 1][j - 1]<<right<<endl;
                }
                dp[i][j] = dp[i][j] < 0 ? dp[i][j] + 1000000007
                                        : dp[i][j] % 1000000007;
            }
        }
        return dp[0][m - 1];
    }
};