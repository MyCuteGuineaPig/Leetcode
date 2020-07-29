//2020 Bottom-up
/*
dp[g][p] 表示当人数为g, profit 为 p 可能的方式
dp[g][P] 表示当人数为g, profit至少为P 可能的方式
 */
class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int mod = pow(10,9)+7;
        vector<vector<long>>dp(G+1, vector<long>(P+1));
        dp[0][0] = 1;
        for(int i = 0; i<group.size(); ++i){
            for(int g = G; g>=0; g--){
                for(int p = P; p>=0; p--){
                    int nxtG = g + group[i];
                    int nxtP = min(P, p+profit[i]);
                    if(nxtG <= G)
                        dp[nxtG][nxtP] = (dp[nxtG][nxtP] + dp[g][p])%mod;
                }
            }
        }
        long res = 0;
        for(int g = 1; g<=G; g++ )
            res = (res + dp[g][P])%mod;
        return res;
    }
};



class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int mod = pow(10,9)+7;
        vector<vector<long>>dp(G+1, vector<long>(P+1)); 
        dp[0][0] = 1;
        for(int i = 0; i<group.size(); ++i){
            for(int g = G; g-group[i]>=0; g--){

                //比如 G = 5,  P = 3, group = 【2，3], profit = [3,3],  i = 0, 更新 dp[2][3] = 1, dp[5][3] = dp[2][3]
                for(int p = 0; p<profit[i] && p <= P; ++p)
                    dp[g][P] = (dp[g][P] + dp[g-group[i]][P-p])%mod;
                
                for(int p = P; p-profit[i]>=0; p--){
                    dp[g][p] = (dp[g][p] + dp[g-group[i]][p-profit[i]])%mod;
                }
            }
        }
        long res = 0;
        for(int g = 1; g<=G; g++ )
            res = (res + dp[g][P])%mod;
        return res;
    }
};


//2020 Bottom-up
class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int mod = pow(10,9)+7;
        vector<vector<long>>dp(G+1, vector<long>(P+1));
        dp[0][0] = 1;
        for(int i = 0; i<group.size(); ++i){
            for(int g = G; g-group[i]>=0; g--){
                for(int p = P; p>=0; p--){
                    int nxtP = min(P, p+profit[i]);
                    dp[g][nxtP] = (dp[g][nxtP] + dp[g-group[i]][p])%mod;
                }
            }
        }
        long res = 0;
        for(int g = 1; g<=G; g++ )
            res = (res + dp[g][P])%mod;
        return res;
    }
};




//TopDown
class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int mod = pow(10,9)+7;
        vector<vector<vector<long>>>dp(group.size()+1, vector<vector<long>>(G+1, vector<long>(P+1,-1)));
        dp[group.size()][0][0] = 1;

        return topDown(G,P, 0,group, profit, dp);
    }
    
    int topDown(int G, int P, int k, vector<int>& group, vector<int>& profit, vector<vector<vector<long>>>&dp){
        if(k == group.size() || G<=0)
            return G >= 0 && P <= 0;
        if(P < 0) P = 0;  //这一步是最关键的
        if(dp[k+1][G][P]>=0)
            return dp[k+1][G][P];
        int mod = pow(10,9)+7;

        dp[k+1][G][P] =(topDown(G, P, k+1, group, profit, dp) + topDown(G-group[k],P-profit[k], k+1,group, profit, dp))%mod;
        
        return dp[k+1][G][P];
    }
};



class Solution {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        memset(memo, -1, sizeof(int)*101*101*101);
        return dfs(G, P, group, profit, group.size()-1);
    }
private:
    int memo[101][101][101];
    long long mod = 1e9+7;
    long long dfs(int g, int p, vector<int>& group, vector<int>& profit, int index) {
        if (index == -1) {
            if (p <= 0) return 1;
            else return 0;
        }
        if (memo[g][p][index] != -1) return memo[g][p][index];
        // not use index
        long long res = dfs(g, p, group, profit, index-1) % mod;
        // use index
        if (g >= group[index]) {
            res += dfs(g-group[index], max(0, p-profit[index]), group, profit, index-1) % mod;
        }
        memo[g][p][index] = res % mod;
        return memo[g][p][index];
    }
};