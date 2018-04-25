/*
629. K Inverse Pairs Array

Given two integers n and k, find how many different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs.

We define an inverse pair as following: For ith and jth element in the array, if i < j and a[i] > a[j] 
then it's an inverse pair; Otherwise, it's not.

Since the answer may be very large, the answer should be modulo 109 + 7.

Example 1:
Input: n = 3, k = 0
Output: 1
Explanation: 
Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
Example 2:
Input: n = 3, k = 1
Output: 2
Explanation: 
The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
Note:
The integer n is in the range [1, 1000] and k is in the range [0, 1000].


*/

/*
For a better understanding, I would use O(n * k ) space instead of O(k) space. It’s easy to write O(k) space version when you understand this DP process.
As @awice said in his Post

For example, if we have some permutation of 1…4

5 x x x x creates 4 new inverse pairs
x 5 x x x creates 3 new inverse pairs
…
x x x x 5 creates 0 new inverse pairs

dp[n][k] denotes the number of arrays that have k inverse pairs for array composed of 1 to n
we can establish the recursive relationship between dp[n][k] and dp[n-1][i]:

if we put n as the last number then all the k inverse pair should come from the first n-1 numbers
if we put n as the second last number then there’s 1 inverse pair involves n so the rest k-1 comes from the first n-1 numbers
…
if we put n as the first number then there’s n-1 inverse pairs involve n so the rest k-(n-1) comes from the first n-1 numbers

dp[n][k] = dp[n-1][k]+dp[n-1][k-1]+dp[n-1][k-2]+…+dp[n-1][k+1-n+1]+dp[n-1][k-n+1]

It’s possible that some where in the right hand side the second array index become negative, 
since we cannot generate negative inverse pairs we just treat them as 0, but still leave the item there as a place holder.

dp[n][k] = dp[n-1][k]+dp[n-1][k-1]+dp[n-1][k-2]+…+dp[n-1][k+1-n+1]+dp[n-1][k-n+1]
dp[n][k+1] = dp[n-1][k+1]+dp[n-1][k]+dp[n-1][k-1]+dp[n-1][k-2]+…+dp[n-1][k+1-n+1]

so by deducting the first line from the second line, we have

dp[n][k+1] = dp[n][k]+dp[n-1][k+1]-dp[n-1][k+1-n]



*/
class Solution {
public:
    int kInversePairs(int n, int k) {
        if(n<=0 || k>n*(n-1)/2) return 0;
        if(k == n*(n-1)/2 || k == 0) return 1;
        static const long long m = 1000000007;
        vector<vector<long long>>dp(2,vector<long long>(k+1));
        for(int i = 2;i<=n; i++){
            dp[i%2][0] = 1;
            for(int j = 1, a = i%2; j<=min(k, i*(i-1)/2); j++){
                dp[a][j] = (dp[a][j-1] + dp[a^1][j])%m;
                if(j>=i)
                    dp[a][j] = (dp[a][j]-dp[a^1][j-i]+m)%m;
            }
        }
        return dp[n%2][k];
    }
};




class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1, vector<int>(k+1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            dp[i][0] = 1;
            for(int j = 1; j <= k; ++j){
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % mod;
                if(j - i >= 0){
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + mod) % mod; 
                    //It must + mod, If you don't know why, you can check the case 1000, 1000
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7;
};