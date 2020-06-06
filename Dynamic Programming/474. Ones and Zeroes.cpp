/*
经典knapsnap problem
dp[i][j][k] means the maximum number of strings we can get from the first i argument strs using limited j number of '0’s and k number of '1’s.
dp[i][j][k] 代表最大长度的string我们可以获得在第i个string，且0的最大个数为j, 且1的最大个数为K
*/
//Bottom-Up
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

//Bottom-Up
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
        return dp[m][n]; // dp[m][n] 一定是解，dp[m][n] 不代表一定用m个0, n个1，而是最多用m个0, n个1
    }
};


//Bottom-Up
class Solution {
public:
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
};





//Top-Down
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {        
        int res = 0;
        vector<vector<vector<int>>>dp(strs.size(), vector<vector<int>>(m+1, vector<int>(n+1,-1)));
        //必须是三维的，因为用，也可以跳过strs[i]
        return topDown(strs, dp, 0, m, n);
        
    }
    
    int topDown(const vector<string>& strs, vector<vector<vector<int>>> &dp, int pos, int m, int n){
        if(pos == strs.size() || m < 0 || n <0 || m == 0 && n == 0)
            return 0;
        
        if(dp[pos][m][n] != -1)
            return dp[pos][m][n];
        
        int i0 = 0, i1 = 0, cur = 0;

        for(auto s: strs[pos]){
            if(s == '0') i0 += 1;
            else i1 += 1;
        }
        
        
                
        if(i0 <= m && i1<=n)
            cur = topDown(strs, dp, pos + 1, m - i0, n-i1)+1;

        cur = max(cur, topDown(strs, dp, pos + 1, m, n));
        return dp[pos][m][n] = cur;
    }
};
//Top-Down
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
        if(m < 0 || n < 0 || m==0 && n==0 || idx >= cache.size() )
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