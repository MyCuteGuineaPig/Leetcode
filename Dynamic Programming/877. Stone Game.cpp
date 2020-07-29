/**
 Approach 1: Just return true
Alex is first to pick pile.
piles.length is even, and this lead to an interesting fact:
Alex can always pick odd piles or always pick even piles!

For example,
If Alex wants to pick even indexed piles piles[0], piles[2], ....., piles[n-2],
he picks first piles[0], then Lee can pick either piles[1] or piles[n - 1].
Every turn, Alex can always pick even indexed piles and Lee can only pick odd indexed piles.

In the description, we know that sum(piles) is odd.
If sum(piles[even]) > sum(piles[odd]), Alex just picks all evens and wins.
If sum(piles[even]) < sum(piles[odd]), Alex just picks all odds and wins.

So, Alex always defeats Lee in this game.

 */


/**
 dp[i][j] 表示person 1 开始拿起，起点是i,j 可以拿到的最大值
 */
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>>dp(n, vector<int>(n));
        int tot = 0;  for(auto i: piles) tot+=i;
        return topDown(piles, dp, 0, n-1) > tot / 2;
    }
    
    int topDown(vector<int>& piles, vector<vector<int>>& dp, int i, int j){
        if(i == j)
            return piles[i];
        if (i>j)
            return 0;
        if (dp[i][j] > 0)
            return dp[i][j];
        dp[i][j] = max(piles[i] + topDown(piles, dp, i+1, j), piles[j]+topDown(piles,dp, i, j-1));
        return dp[i][j];   
    }
};


//Bottom-up
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>>dp(n, vector<int>(n));
        int tot = 0;  
        for(int i = 0; i<n; ++i) {tot+= i; dp[i][i] = piles[i];}
        for(int r = 1; r<n; ++r){
            for(int l = r-1; l>=0; --l){
                dp[l][r] = max(dp[l+1][r] + piles[l], dp[l][r-1] + piles[r]);
            }
        }
        
        
        return dp[0][n-1] > tot / 2;
    }
};

/*

dp[i][j] means the biggest number of stones you can get more than opponent picking piles in piles[i] ~ piles[j].
 */
class Solution {
public:
    bool stoneGame(vector<int>& p) {
        int n = p.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) dp[i][i] = p[i];
        for (int d = 1; d < n; d++)
            for (int i = 0; i < n - d; i++)
                dp[i][i + d] = max(p[i] - dp[i + 1][i + d], p[i + d] - dp[i][i + d - 1]);
        return dp[0][n - 1] > 0;
    }
};


//O(n) space
class Solution {
public:
    bool stoneGame(vector<int>& p) {
        vector<int> dp = p;
        for (int d = 1; d < p.size(); d++)
            for (int i = 0; i < p.size() - d; i++)
                dp[i] = max(p[i] - dp[i + 1], p[i + d] - dp[i]);  // dp[i] 表示 从i 到 i+d 可以得到的分数
                // dp[i + 1]， dp[i] 是d-1 结果,  dp[i+1]: 表示 i 到 i+d (i+1+d-1),  dp[i] 表示 i 到 i + d -1 
        return dp[0] > 0;
    }
};



class Solution {
public:
    
    int findwin(vector<int>&piles, int left, int right, vector<vector<int>>& dp){
        if(left > right)
            return 0;
        if(dp[left][right] != -1)
            return dp[left][right];
        int pos1 = piles[left] + min(findwin(piles, left + 2, right, dp), findwin(piles, left+1, right-1, dp));
        int pos2 = piles[right] + min(findwin(piles, left+1, right-1, dp), findwin(piles, left, right-2, dp));
        return dp[left][right] = max(pos1, pos2);
    }
    
    bool stoneGame(vector<int>& piles) {
        
        vector<vector<int>> dp(piles.size(), vector<int>(piles.size(), -1));
        int left = 0;
        int right = piles.size()-1;
        int alex = findwin(piles, left, right, dp);
        int sum = 0;
        for(int i=0; i<piles.size(); i++)
            sum += piles[i];
        return alex > sum - alex;
    }
};

