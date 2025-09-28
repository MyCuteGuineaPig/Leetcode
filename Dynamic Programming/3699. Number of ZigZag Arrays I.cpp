/*

dp[i][0][x]: 长度为i+1,down 以x结尾的zigzag array 数量
    dp[i][0][x]: sum (dp[i-1][1][y])  y > x

dp[i][1][x]: 长度为i+1,up 以x结尾的zigzag array 数量
    dp[i][1][x]: sum (dp[i-1][0][y])  y < x

 */

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        r -= l; l = 0;
        vector<vector<vector<long>>>dp(n, vector<vector<long>>(2, vector<long>(r+1)));
        vector<vector<vector<long>>>dpsum(2, vector<vector<long>>(2, vector<long>(r+1)));
        vector<long>presum_left(n);
        for(int x = l; x <= r; ++x){
            dp[0][0][x] = 1;
            dp[0][1][x] = 1;
            dpsum[0][0][x] =  1*(x-l + 1);
            dpsum[0][1][r-(x-l)] =  1*(x-l + 1);
        }
        long mod = 1e9  + 7;
        for(int i = 1; i < n; ++i){
            for(int x = l; x <= r; ++x) {
                dp[i][0][x] = (x == r) ? 0: dpsum[(i-1)%2][1][x+1];
                dpsum[i%2][0][x] = (dp[i][0][x] +  (x == 0 ? 0: dpsum[i%2][0][x-1])) % mod;
            }
            for(int x = r; x>=l; --x){
                dp[i][1][x] = (x == 0) ? 0 : dpsum[(i-1)%2][0][x-1];
                dpsum[i%2][1][x] = (dp[i][1][x] +  (x == r ? 0: dpsum[i%2][1][x+1])) % mod;
            }
        }
        long res = 0;
        for(int x = l; x <= r; ++x){
            res =  (res + dp[n-1][0][x] + dp[n-1][1][x]) % mod;
        }
        return res;
    }
};

/*
State:

dp[v] = number of zigzag arrays ending at value v.

Transition:

Odd step → dp[v] = sum(dp[u]) for u < v. -> increase

Even step → dp[v] = sum(dp[u]) for u > v. -> decrease

Use prefix sums in left-to-right or right-to-left order to update efficiently.

Result:

res = 2 * sum(dp) % MOD (factor 2 accounts for up/down symmetry).

Complexity
With rolling array + prefix sum trick:
Time O(n(r - l))
Space O(n)


n =3
l = 1
r = 3


 up i= 1  v= 0 dp[v] 0
 up i= 1 v=  1 dp[v] 1
 up i= 1 v=  2 dp[v] 2
 down i= 2 v 2 dp[v] 0
 down i= 2 v 1 dp[v] 2
 down i= 2 v 0 dp[v] 3

 up时候 dp[l] 一定是0， 因为没有上个数没有比 l更小的
 down的时候, dp[r] 一定是0, 因为没有上个数没有比 r更大的
*/


class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int mod = 1e9+7;
        r -= l;  l = 0;
        vector<long>dp(r+1, 1);
        for(int i = 1; i < n; ++i){
            int pre = 0, pre2; 
            if ( i & 1) {
                for(int v = 0; v <=r; ++v) {
                    pre2 = pre + dp[v];
                    dp[v] = pre;
                    pre = pre2 % mod;
                }
            } else {
                for(int v = r; v >=0 ; --v) {
                    pre2 = pre + dp[v];
                    dp[v] = pre;
                    pre = pre2 % mod;
                }
            }
        }
        long res = 0;
        for(auto i: dp)
            res = (res + i) % mod;
        return 2*res % mod; //因为考虑到只在每个i算 up or down not both, 所以乘以2
    }
};