
/*

 k  0  1  2  3   4  5   6   7   8
 n 
 1  1
 2  1  1
 3  1  2  2  1
 4  1  3  5  6   5   3   1
 5  1  4  9  15  20  22  20  15  9
 6  1  5  14 29  49  71  90  101 101

 dp[i][j] 表示 1~i 组成的数组，有j个inverse pair的数组个数
 dp[i][j] = dp[i-1][j](append i 到原有数组后) + dp[i][j-1](交换i 与前一个数的位置)
 if j >= i: 
      dp[i][j] -= dp[i-1][j-i] (表示i已经到最左侧，无法交换)
      dp[i-1][j-i]产生dp[i][j-i]时。 把i append 到最右侧，通过i-1个switch, i已经到最左侧



比如 n=3, k = 1:  (1,3,2),  (2,1,3)
    n=3, k = 2:   (2,3,1), (3,1,2)
    n=3, k = 3:   (3,2,1)

那么, n = 4, k = 0:
    对于n=3, k = 0, 把 4 append到数的后面, 且不破坏原数组顺序, (1,2,3) + 4

那么, n = 4, k =1:
    对于n=3, k = 1, 把 4 append到数的后面 则继续保持 inverse pair 为1且不破坏原数组顺序, (1,3,2) + 4, (2,1,3) + 4 
    对于n=4, k = 0, 交换4和前一个数的位置, 产生一个新的pair,  (1,2,4,3)  =} 来自于 n = 3, k= 0

那么 n = 4, k = 2
     对于n=3, k = 2, 把 4 append到数的后面, (2,3,1)+4, (3,1,2) + 4
     多于n=4, k = 1, 交换4 与前一个数的位置，产生一个新的pair, 
         (1,3,2, 4) =》 (1,3,4,2),  (2,1,3,4) => （2,1,4,3),     =} 来自于 n = 3, k= 1
         (1,2,4,3) => (1,4,2,3)                                 =} 来自于 n = 3, k= 0  

 那么 n = 4, k = 3
     对于n=3, k = 3, 把 4 append到数的后面, (3,2,1) + 4 
     对于  n=4, k = 2, 交换4 与前一个数的位置，产生一个新的pair, 
        （2，3，1，4) => (2,3,4,1),  (3,1,2,4) = > (3,1,4,2)      =} 来自于 n = 3, k= 2
         (1,3,4,2) => (1,4,3,2),  (2,1,4,3) => (2,4,1,3),        =} 来自于 n = 3, k= 1
        (1,4,2,3) => (4,1,2,3)   =} 来自于 n = 3, k= 0

 那么 n = 4, k = 4
     对于n=3, k = 4, 没有结果
     对于 n=4, k = 3, 交换4 与前一个数的位置，产生一个新的pair, 
     （3，2，1，4) =>  (3,2,4,1),                                 =} 来自于 n = 3, k= 3
      (2,3,4,1) =>  (2,4,3,1), (3,1,4,2) = > (3,4,1,2)           =} 来自于 n = 3, k= 2
      (1,4,3,2) =>  (4,1,3,2),  (2,4,1,3) =>  (4,2,1,3)          =} 来自于 n = 3, k= 1
    *** 减去 dp[3][0]:  因为当 n =4, k =3 时， 来自于 n = 3, k = 0 的pair, 4 已经在最左侧( (4,1,2,3) )，不能移动

那么 n=4, k = 5
     对于 n = 4, k =4, 交换4 与前一个数的位置，产生一个新的pair, 
       (3,2,4,1) =>  (3,4,2,1),                                 =} 来自于 n = 3, k= 3
       (2,4,3,1) => (4,2,3,1), (3,4,1,2) => (4,3,1,2)           =} 来自于 n = 3, k= 2
     *** 减去 dp[3][1]:  因为当 n =4, k =4 时， 来自于 n = 3, k = 1 的pair, 4 已经在最左侧( (4,1,3,2), (4,2,1,3) )，不能移动

不会有重复：
 假设 n = i, k = i*(i-1)/2 时没有重复
 那么 当 n = i+ 1, 所有的数都是从 n = i 过来的，只不过是把i + 1 append 到n = i 右侧，然后不断左移动，所以不会有重复

i*(i-1) /2 是 C n, 2 的结果, 表示从i里选择2对 有多少对
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

/* 
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


This solution is too slow! 可以转化成方法一:
Mathematical Proof:
dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + dp[i-1][j-2] + ......+dp[i-1][j-i+1] as per definition ---(1)
                        /              /                     /
But dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ....+ dp[i-1][j-i+1] + dp[i-1][j-i] as per definition ---(2)

From (1) and (2)

dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + ......+dp[i-1][j-i+1]) + dp[i-1][j-i] - dp[i-1][j-i]
=>dp[i][j] = dp[i-1][j] + (dp[i-1][j-1] + ......+dp[i-1][j-i+1] + dp[i-1][j-i]) - dp[i-1][j-i]
=>dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-i]


*/
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j < i; ++j){ // In number i, we can create 0 ~ i-1 inverse pairs 
                for(int m = 0; m <= k; ++m){ //dp[i][m] +=  dp[i-1][m-j]
                    if(m - j >= 0 && m - j <= k){
                        dp[i][m] = (dp[i][m] + dp[i-1][m-j]) % mod; 
                    }
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7;
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
                    //It must + mod, If  don't know why, you can check the case 1000, 1000
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7;
};