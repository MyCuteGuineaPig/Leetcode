/*

把每个数乘以1，0，-1，最后的sum是0

. Given [1,2,3,4,5,6], we have 1*0 + 2 + 3 - 4 + 5 - 6 = 0, the sum of all positive numbers is 2 + 3 + 5 = 10. 
The answer is 10.

dp[i][j]:表示前i个数的和可以是 j - 5000, dp[0][5000] = true;
Then:
dp[i+1][j] = dp[i][j-rods[i]] | dp[i][j+rods[i]] | dp[i][j]
maxsum[i+1][j]: 表示前i个数最大的sum of posiive numbers 当前i个数的sum 可以是j-5000
*/
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        vector<vector<int>>dp(n+1,vector<int>(10001));
        vector<vector<int>>maxsum(n+1,vector<int>(10001));
        dp[0][5000] = 1;
        for(int i = 0; i<n;++i){
            for(int j = 0; j<10001; ++j){
                if(j-rods[i]>=0 && dp[i][j-rods[i]]){ //把rods[i]乘以1
                    dp[i+1][j] = 1;
                    maxsum[i+1][j] = maxsum[i][j-rods[i]] + rods[i];
                }
                if(dp[i][j]){//把rods[i]乘以0
                    dp[i+1][j] = 1;
                    maxsum[i+1][j] = max(maxsum[i+1][j]  , maxsum[i][j]);
                }
                if(j+rods[i] < 10001 && dp[i][j+rods[i]]){ //把rods[i]乘以-1
                    dp[i+1][j] = 1;
                    maxsum[i+1][j] = max(maxsum[i+1][j],maxsum[i][j+rods[i]]);
                }

            }
        }
        return maxsum[n][5000];
    }
};


class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        int sum = accumulate(rods.begin(), rods.end(), 0);
        int limit = 2*sum + 1;
        vector<vector<int>> dp(n+1, vector<int>(limit, INT_MIN));  // INT_MIN means no solution
        dp[0][sum] = 0;  // Special case when no rods left and diff is 0 (sum - 0)
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < limit; j++) {
                // Putting ith rod in g0
                if ((j - rods[i-1]) >= 0 && dp[i-1][j - rods[i-1]] != INT_MIN)
                    dp[i][j] = max(dp[i][j], dp[i-1][j - rods[i-1]] + rods[i-1]);
                // Putting ith in g1
                if ((j + rods[i-1]) < limit && dp[i-1][j + rods[i-1]] != INT_MIN)
                    dp[i][j] = max(dp[i][j], dp[i-1][j + rods[i-1]]);
                // Ignoring ith rod
                if (dp[i-1][j] != INT_MIN)
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
        }
        return dp[n][sum];
    }
};




/*
min(O(SN/2), O(3^N/2 * N)

dp[d] 表示最大的 max(min((a,b)  with pair difference a-b=d )

If have a pair of sum (a, b) with a > b, then dp[a - b] = b

Example
dp is initializes with dp[0] = 0;

Assume we have an init state like this
------- y ------|----- d -----|
------- y ------|

case 1
If put x to tall side
------- y ------|----- d -----|----- x -----|
------- y ------|

We update dp[d + x] = max(dp[d + x], y )

case 2.1
Put x to low side and d >= x:
-------y------|----- d -----|
-------y------|--- x ---|

We update dp[d-x] = max(dp[d - x], y + x)

case 2.2
Put x to low side and d < x:
------- y ------|----- d -----|
------- y ------|------- x -------|
We update dp[x - d] = max(dp[x - d], y + d)

case 2.1 and case2.2 can merge into dp[abs(x - d)] = max(dp[abs(x - d)], y + min(d, x))

 */


/*
pseudo code


dp[d] = a , the highest lower tower of a pair which have a height gap of d  
for x in rods:
     x has not been used in any pairs of towers yet 
     use it to update dp

return dp[0]
 */
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;
        for (int x : rods) {
            unordered_map<int, int> cur(dp);
            for (auto it: cur) {
                int d = it.first;
                dp[d + x] = max(dp[d + x],cur[d]);
                dp[abs(d - x)] = max(dp[abs(d - x)], cur[d] + min(d, x));
            }
        }
        return dp[0];
    }
};



/**
 Get TLE for below 
int tallestBillboard(vector<int>& rods, int i = 0, int s1 = 0, int s2 = 0) {
  if (i >= rods.size()) return s1 == s2 ? s1 : 0;
  return max({ tallestBillboard(rods, i + 1, s1, s2), 
               tallestBillboard(rods, i + 1, s1 + rods[i], s2), 
               tallestBillboard(rods, i + 1, s1, s2 + rods[i]) });
}

需要figure out a way to memoisation, 如果记录s1, 2 , require a lot of memory (MLE or TLE)
memoise delta:  abs(s1 - s2)

比如 for i rod, s1 = 50, s2 = 30,  到最后的一个s1 = s2 = 200, 记录m[i][50-30] = 200 - 50 = 150; 
荣誉感以以后到 i, s1 = 100 and s2 = 80. 可以直接return 结果 150 + 100 = 250 


Just wanted to add few more points why we are considering storing the absolute difference here in DP. 
If we store the actual sums s1 and s2, the problem description says that the sum of the array would be at max 5000. 
So the values of s1 and s2 should be at max 5000 and the rods length is at max 20. 
So we would be creating dp[20][5000][5000] which would hold 20 * 5000 * 5000 * 4 (4 bytes for int). 
So it would be around ~ 1.86 GB.

 */
class Solution {
public:
    int dfs(vector<int>& rs, int i, int s1, int s2, int m_sum, vector<vector<int>> &m) {
      if (s1 > m_sum || s2 > m_sum) return -1;
      if (i >= rs.size()) return s1 == s2 ? s1 : -1;
      if (m[i][abs(s1 - s2)] == -2) {
        m[i][abs(s1 - s2)] = max(-1, max({ dfs(rs, i + 1, s1, s2, m_sum, m),
          dfs(rs, i + 1, s1 + rs[i], s2, m_sum, m), dfs(rs, i + 1, s1, s2 + rs[i], m_sum, m) }) - max(s1, s2));
      }
      return m[i][abs(s1 - s2)] + (m[i][abs(s1 - s2)] == -1 ? 0 : max(s1, s2));
    }
    int tallestBillboard(vector<int>& rods) {
      int m_sum = accumulate(begin(rods), end(rods), 0) / 2;
      vector<vector<int>> m(rods.size(), vector<int>(m_sum + 1, -2));
      return max(0, dfs(rods, 0, 0, 0, m_sum, m));
    }
};



/*
dp's key represents the sum of left billboard - the sum of right billboard,
     the value represents the largest sum of left billboard

pair sum(a,b)
dp[abs(a-b)] = max(a,b)
 */
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;
        for(int ele:rods){
            unordered_map<int, int> temp;
            temp.insert(dp.begin(), dp.end());
            for(auto& it: dp){
                int dif = it.first;
                temp[dif+ele] = max(temp[dif+ele], dp[dif]+ele);
                temp[dif-ele] = max(temp[dif-ele], dp[dif]);
            }
            dp.clear();
            dp.insert(temp.begin(), temp.end());
        }
        
        return dp[0];
    }

};