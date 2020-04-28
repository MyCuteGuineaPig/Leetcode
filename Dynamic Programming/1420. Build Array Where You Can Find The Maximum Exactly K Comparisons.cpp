/* 
ways[i][j][k] be the number of ways to construct an array of length i with maximum element equal to j at a search cost of k.

1. Clearly, we require ways[i][j][k] += j * ways[i - 1][j][k]. Why? 
    Because if we have an array of length i - 1 with maximum element equal to j at a search cost of k, 
    then we can just append any element from [1, 2, ... j] to this array, 
    and we end up with an array of length i with maximum element equal to j at a search cost of k. 
    Note that neither the search cost nor the maximum element change since we're only appending elements from [1,2, ..., j]. 
    Only the length changes by one.

2. We also require ways[i][j][k] += SUM from x=1 to j-1 of ways[i - 1][x][k - 1] (the sum is inclusive on both ends). 
    This is true because if we have an array of length i - 1 with maximum element (strictly) 
    less than j at a search cost of k - 1, then we can simply append the element j to the end of this array 
    (which adds a comparison cost of one), and we obtain a valid solution.

Now the answer is just the sum over all ways[i][x][k] from x = 1 to k because there is no constraint on what the maximum element should be.

*/
//# Time:  O(n * m^2 * k)
class Solution {
public:
    /* let ways[i][j][k] = # ways to construct an array of length i with max element equal to j and a search cost of k. */
    long long ways[51][101][51];
    const int MOD = 1e9 + 7;
    
    int numOfArrays(int n, int m, int k) {
        memset(ways, 0, sizeof(ways));
        
		/* There are our base cases. For each index 1 <= j <= m, we require ways[1][j][1] = 1 because the array consisting of only the element j
			has length 1, maximum element j, and it has a search cost of 1. */
        for (int j = 1; j <= m; j++) {
                ways[1][j][1] = 1;
        }
        
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= m; b++) {
                for (int c = 1; c <= k; c++) {
                    long long s = 0;

		            /* In this first case, we can append any element from [1, b] to the end of the array. */
                    s = (s + b * ways[a - 1][b][c]) % MOD;
                    
		           /* In this second case, we can append the element "b" to the end of the array. */
                    for (int x = 1; x < b; x++) {
						s = (s + ways[a - 1][x][c - 1]) % MOD;
                    }
					
                    ways[a][b][c] = (ways[a][b][c] + s) % MOD;
                }
            }
        }

        long long ans = 0;
        for (int j = 1; j <= m; j++) {
            ans = (ans + ways[n][j][k]) % MOD;
        }
        
        return int(ans);
    }
};

//# Time:  O(n * m * k)
class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        unordered_map<long, unordered_map<long, unordered_map<long,long>>> dp;
        unordered_map<long, unordered_map<long, unordered_map<long,long>>> prefix_dp;
        int mod = 1000000007;
        for(int b = 1; b <= m; ++b){
            dp[1][b][1] = 1;
            prefix_dp[1][b][1] = (prefix_dp[1][b-1][1] + dp[1][b][1]) % mod;
        }
        
        for(int a = 2; a <=n ; ++a)
        {
            for(int b = 1; b<=m; ++b){
                for(int c = 1; c <=k ; ++c){
                    //cout << a <<" b" <<b<<" c "<<c<<endl;
                    dp[a][b][c] = (dp[a][b][c] + ((dp[a-1][b][c]*b)%mod + 
                        prefix_dp[a-1][b-1][c-1]) % mod) % mod;
                    prefix_dp[a][b][c] = (prefix_dp[a][b][c] +( prefix_dp[a][b-1][c] + dp[a][b][c]) % mod) % mod;
                }
            }
        }
        return prefix_dp[n][m][k];   
    }
};


/**
 * DFS
 */

class Solution {
public:
    int dp[51][101][51] = {};
    int dfs(int n, int m, int cost, int i, int max_val) {
        if (n == i)
            return cost == 0;
        if (cost < 0 || m - max_val < cost) //比如 m = 5, max_val = 3, cost = 3, 
            return 0;                      //无法保证 用完cost 来更新max_val
        
        if (dp[i][max_val][cost] > 0)
            return dp[i][max_val][cost] - 1;
        int val = 0;
        for (auto ni = 1; ni <= m; ++ni) {
            val = (val + dfs(n, m, cost - (max_val < ni), i + 1, max(max_val, ni))) % 1000000007;
        }
        dp[i][max_val][cost] = val + 1; //避免是是0, if (dp[i][max_val][cost] > 0) 返回不了
        return val;
    }
    
    int numOfArrays(int n, int m, int k) {
        return dfs(n, m, k, 0, 0);
    }
};


class Solution {
public:
    unordered_map<int, unordered_map<int, unordered_map<int,int>>> dp;
    int dfs(int n, int m, int cost, int i, int max_val) {
        if (n == i)
            return cost == 0;
        if (cost < 0 || m - max_val < cost) //比如 m = 5, max_val = 3, cost = 3, 
            return 0;                      //无法保证 用完cost 来更新max_val
        
        if (dp.count(i) && dp[i].count(max_val) && dp[i][max_val].count(cost))
            return dp[i][max_val][cost];
        int val = 0;
        for (auto ni = 1; ni <= m; ++ni) {
            val = (val + dfs(n, m, cost - (max_val < ni), i + 1, max(max_val, ni))) % 1000000007;
        }
        dp[i][max_val][cost] = val; //避免是是0, if (dp[i][max_val][cost] > 0) 返回不了
        return val;
    }
    
    int numOfArrays(int n, int m, int k) {
        return dfs(n, m, k, 0, 0);
    }
};


class Solution {
public:
    int numOfArrays(int arrSize, int maxVal, int maxCost) {
        using ll=long long;
        // dp[arrSizeSoFar][maxValSoFar][costSoFar]
        vector<vector<vector<ll>>> dp(arrSize+1,vector<vector<ll>>(maxVal+1, vector<ll>(maxCost+1,0)));
        for(int v=1;v<=maxVal;v++) dp[1][v][1]=1;    // for each array of size 1 just 1 way of making it

        // emulate building a sequence: add a new num to the existing sequence and check the cost
        for(int s=2;s<=arrSize;s++) {                // for each size  
            for(int v=1;v<=maxVal;v++) {             // for each maxVal so far
                for(int c=1;c<=maxCost;c++) {        // for each cost so far
                    for(int vv=1;vv<=maxVal;vv++) {  // try each new num in range [1...maxVal]
                        // if new num updates the maxValSoFar, increase the cost and save the num of ways for the new maxVal
                        if(vv<=v) dp[s][v][c] +=dp[s-1][v][c],   dp[s][v][c]%=1000000007;
                        else      dp[s][vv][c]+=dp[s-1][v][c-1], dp[s][vv][c]%=1000000007;
                    }
                }
            }
        }
        
        ll res=0;
        for(int v=1;v<=maxVal;v++)
            res+= dp[arrSize][v][maxCost], res%=1000000007;
        
        return res;        
    }
};