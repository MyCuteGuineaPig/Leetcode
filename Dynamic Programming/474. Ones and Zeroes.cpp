/*
474. Ones and Zeroes

In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

Note:
The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.
Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".

*/

/*
经典knapsnap problem
dp[i][j][k] means the maximum number of strings we can get from the first i argument strs using limited j number of '0’s and k number of '1’s.
dp[i][j][k] 代表最大长度的string我们可以获得在第i个string，且0的最大个数为j, 且1的最大个数为K
*/
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<vector<int>>>dp(strs.size()+1,vector<vector<int>>(m+1, vector<int>(n+1,0)));
        for(int i = 0; i<strs.size();i++){
            int c0 = 0, c1 = 0;
            for(auto s: strs[i])
            {
                if(s=='1') c1++;
                else if(s=='0') c0++;
            }
            for(int j = 0; j<=m; j++){
                for(int k = 0; k<=n; k++){
                    if(j>=c0 && k>=c1){
                        dp[i+1][j][k] = max(dp[i][j][k], dp[i][j-c0][k-c1]+1);
                    }
                    else 
                        dp[i+1][j][k] = dp[i][j][k];
                }
            }
        }
        return dp[strs.size()][m][n];
    }
};


class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>>dp(m+1, vector<int>(n+1,0));
        for(int i = 0; i<strs.size();i++){
            int c0 = 0, c1 = 0;
            for(auto s: strs[i])
            {
                if(s=='1') c1++;
                else if(s=='0') c0++;
            }
            for(int j = m; j>=c0; j--){ //必须从大到小，本来这次i依靠i-1的值，如果从小到大，这次i的值会依靠这次i的数
                for(int k = n; k>=c1; k--){
                    dp[j][k] = max(dp[j][k], dp[j-c0][k-c1]+1);
                }
            }
        }
        return dp[m][n];
    }
};

int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    
    for (auto &s: strs) {
        int ones = count(s.begin(), s.end(), '1');
        int zeros= s.size()-ones;
        for (int i=m; i>=zeros; i--) 
            for (int j=n; j>=ones; j--)
                dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones]+1);
    }
    return dp[m][n];
}

/*

对于
["10","0001","111001","1","0"]  
5
3
 i 0               i 1
0 0 0 0         0 0 0 0 
0 0 0 0         0 1 1 1 
0 0 0 0         0 1 1 1 
0 0 0 0         0 1 1 1 
0 0 0 0         0 1 1 1 
0 0 0 0         0 1 1 1 

 i 2            i 3
0 0 0 0         0 0 0 0 
0 1 1 1         0 1 1 1 
0 1 1 1         0 1 1 1 
0 1 1 1         0 1 1 1 
0 1 2 2         0 1 2 2 
0 1 2 2         0 1 2 2 
 

 i 4             i 5
0 1 1 1         0 1 1 1 
0 1 2 2         1 2 2 2 
0 1 2 2         1 2 3 3 
0 1 2 2         1 2 3 3 
0 1 2 3         1 2 3 3
0 1 2 3         1 2 3 4 


*/


class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) 
    {
        vector<pair<int,int>> cache;
        for(string & s : strs)
        {
            pair<int,int> p;
            for(char & c : s)
            {
                if(c == '0')
                    p.first++;
                else
                    p.second++;
            }
            cache.push_back(p);
        }
        auto comp = [](auto & a, auto & b)
        {
            return a.first + a.second < b.first + b.second;
        };
        vector<vector<int>>visited(m+1,vector<int>(n+1,-1));
        sort(cache.begin(),cache.end(),comp);
        return getmax(visited,cache,m,n,0);
    }
    int getmax(vector<vector<int>> & visited,vector<pair<int,int>> &cache, int m , int n, int idx)
    {
        if(m <= 0 && n <= 0)
            return 0;
        if(m < 0 || n < 0)
            return 0;
        if(idx >= cache.size())
            return 0;
        if(visited[m][n] >= 0)
            return visited[m][n];
        int ans = 0;
        for(int i = idx ; i < cache.size() ; i++)
        {
            if(cache[i].first <= m && cache[i].second <= n)
            {
                ans = max(ans, 1 + getmax(visited,cache,m-cache[i].first,n-cache[i].second,i+1));
            }
        }
        visited[m][n] = ans;
        return ans;
    }
};