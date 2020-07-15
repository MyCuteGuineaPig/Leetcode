/*

        a  b  c  a  b  c

    a   1  2  3  3  4  5
    b      1  2  3  3  4 
    c         1  2  3  3 
    a            1  2  3 
    b               1  2
    c                  1

        a  a  a  b  b  b

    a   1  1  1  2     
    a      1  1  2      
    a         1  2     1 
    b            1  1  1 
    b               1  1
    b                  1




*/

/* 
dp[i][j]: 从i 到 j 最少的print次数
if s[i] == s[j]: 
    dp[i][j] = min(dp[i+1][j], dp[i][j-1])
else:
    dp[i][j] = min(dp[i][k] + dp[k+1][j]) for k in [i,j-1]

一个容易犯的错误: 
    if s[i] != s[j]:
        dp[i][j] = min(dp[i+1][j], dp[i][j-1])+1

比如 s= "ddaacca"
    s[0] != s[6]:
        s[1:] = "daacca", dp[1][6] = 3 
        s[0:6] = "ddaacc", dp[1][6] = 3
      dp[i][j] = min(dp[i+1][j], dp[i][j-1])+1 = 4
      
      但是正确应该是 = 3
        s[0:2] = "dd", dp[0][1] = 1
        s[2:] = "aacca", dp[2][6] = 2
        dp[i][j] =  3 
*/

//2020
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        if(n == 0)
            return 0;
        vector<vector<int>>dp(n, vector<int>(n, n+1));
        for(int r = 0; r< n; ++r){
            dp[r][r] = 1;
            for(int l = r-1; l>=0; --l){
                if(s[l] == s[r])
                    dp[l][r] = min(dp[l+1][r], dp[l][r-1]); 
                    //dp[l][r] = dp[l][r-1]; dp[l][r] = dp[l+1][r];  都可以, 
                    /*  比如 axxxxa
                        因为 dp[l+1][r] 是xxxxa 的 minimum print, 包括了右侧的a
                            dp[l][r-1] 是axxxx 的 minimum print, 包括了左侧侧的a
                        且 s[l] = s[r] = a都, 所以 dp[l+1][r] = dp[l][r-1]
                     */
                else{
                    for(int k = l; k<r; ++k)
                        dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
                }
            }
        }

        return dp[0][n-1];
    }
};

//topDown 2020
class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        return topDown(dp, s, 0, n-1);
    }
    
    int topDown(vector<vector<int>>&dp, const string& s, int l, int r){
        if(l >= r)
            return l == r;
        if(dp[l][r] > 0)
            return dp[l][r];
        if(s[l] == s[r])
            return dp[l][r] = topDown(dp, s, l, r-1);
        else{
            int res = r - l+1;
            for(int k = l; k < r; ++k){
                res = min(res, topDown(dp, s, l, k)+topDown(dp, s, k+1, r));
            }
            return dp[l][r] = res;
        }
    }
};

/**
 Method 2: 

dp[i][i] = 1: 
dp[i][i + 1]
    dp[i][i + 1] = 1 if s[i] == s[i]
    dp[i][i + 1] = 2 if s[i] != s[i+1]


We can further divide the substring to two parts: 
    start -> start+k and start+k+1 -> start+len. It is something as following:
    
    index |start  ...  start + k| |start + k + 1 ... start + len|
    char  |  a    ...       b   | |      c       ...      b     |

As shown above, if  s[start + k] == s[start + len], we can make it in one turn when we print this character (i.e. b here)

    dp[start][start+len] = dp[start][start + k] + dp[start + k + 1][start + len] - 1


 */
class Solution {
public:
    int strangePrinter(string s) {
        if(s == "") return 0;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int> (n, n));
        for(int i = 0; i < n; i++) dp[i][i] = 1;
        
        for(int j = 0; j < n; j++)
            for(int i = j; i >= 0; i--)
                for(int k = i; k < j; k++)
                    if(s[k] == s[j]) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] - 1);
                    //不可以是 dp[i][k-1] + dp[k][j] - 1, 因为 当k = 0, k -1 = -1 
                    else dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);

        return dp[0][n-1];
    }
};


// Top-Down 2020

//Top-Down
class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        return topDown(dp, s, 0, n-1);
    }
    
    int topDown(vector<vector<int>>&dp, const string& s, int l, int r){
        if(l >= r)
            return l == r;
        if(dp[l][r] > 0)
            return dp[l][r];
        int res = r- l + 1;
        for(int k = l; k < r; ++k)
            if(s[k] == s[r])
                res = min(res, topDown(dp, s, l, k)+topDown(dp, s, k+1, r-1));
            else 
                res = min(res, topDown(dp, s, l, k)+topDown(dp, s, k+1, r));
        return dp[l][r] = res;
    }
};


class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int i=n-1;i>=0;i--){
            dp[i][i] = 1;
            for(int j=i+1;j<n;j++){
                dp[i][j]= 1+dp[i+1][j]; 
                /*                                                  
                dp[i][j]= 1+dp[i+1][j]; 
                假设是 加s[i] + s[i+1:j], 已知dp[i+1][j] 是最小的print 对于s[i+1:j]
                所以后面检测条件是s[i] = s[k] for k in [k+1, j] 看有没有可以把s[i] 和 s[k] 合并成一个print
                    比如:   a baa, 
                            -  dp[0][3] = 2 + 1 = 3, 
                            -  s[2] = s[0], dp[0][3] 更新为 dp[1][1] + dp[2][3] = 2
                */

                for(int k=i+1;k<=j;k++){
                    if(s[i]==s[k]) 
                        dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);  //注意是 i + 1, 因为看i能不能和k 合成一个print
                        //i 和 k可以一起print, 所以s[i:k] 需要的print 次数是 dp[i+1][k-1]
                }
                /** Inner For loop 也可以这么写
                 for(int k=i;k<j;k++)
                    if(s[i]==s[k+1]) //不可以是 s[k] = s[j] 因为dp[i][k-1] 还没有生成当
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]); 
                 */
            }
                
        }
        return dp[0][n-1];
    }
};



//Top-Down
class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        return topDown(dp, s, 0, n-1);
    }
    
    int topDown(vector<vector<int>>&dp, const string& s, int l, int r){
        if(l >= r)
            return l == r;
        if(dp[l][r] > 0)
            return dp[l][r];
        int res = topDown(dp, s, l+1, r)+1;
        for(int k = l+1; k <= r; ++k)
            if(s[l] == s[k])
                res = min(res, topDown(dp, s, l+1, k-1)+topDown(dp, s, k, r));
                //or res = min(res, topDown(dp, s, l, k-1)+topDown(dp, s, k+1, r));
        return dp[l][r] = res;
    }
};
 

class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        if(n==0) return 0;
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int i=n-1;i>=0;i--){
            dp[i][i] = 1;
            for(int j=i+1;j<n;j++){
                dp[i][j]= 1+dp[i][j-1];  
                /*
                 dp[i][j]= 1+dp[i][j-1]; 
                假设是 s[i:j-1] + s[j], 已知dp[i][j-1] 是最小的print 对于s[i:j-1]
                所以后面检测条件是s[j] = s[k] for k in [i, j-1] 看有没有可以把s[j] 和 s[k] 合并成一个print
                    比如:   aba a, 
                            -  dp[0][3] = 2 + 1 = 3, 
                            -  s[2] = s[3], dp[0][3] 更新为 dp[0][2] + dp[3][2] = 2
                */
                
                
                 */
                for(int k=i;k<j;k++){
                    if(s[k]==s[j]) 
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j-1]); 
                }
            }
                
        }
        return dp[0][n-1];
    }
};
