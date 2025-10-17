/*

dp[i] = cur : 表示组成i的sum 的方式有cur bitset 种
        比如 cur = 5, 110, 可以是 2个数相加， 也可以是3个数相加
        比如 cur = 7, 111, 可以是1个数，也可以是两个数相加，也可以是3个数相加
 */

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(), tot = accumulate(nums.begin(), nums.end(), 0), m = n/2;
        bool hassolution = false;
        for(int i = 0; i <=m; ++i)
            if (tot * i % n == 0) {
                hassolution = true;
                break;
            }
        if (!hassolution) return false;
        vector<int>dp(tot+1);
        dp[0] = 1; 
        for(int i = 0; i < n; ++i){
            for(int cur = tot - nums[i]; cur>=0; --cur){
                if (!dp[cur]) continue; 
                dp[cur + nums[i]] |= (dp[cur] << 1);  
                //假如dp[10] = 5 (110)  到10的可以是两个数相加，也可以是三个数
            }
            dp[nums[i]] |= (1 << 1);
        }
        
        for(int len = 1; len <= m; ++len) {
            if (tot *len % n == 0 && (dp[tot * len / n] & (1 << len)))
                return true; 
        }
        return false;
    }
};


/*
  totalSum/n = Asum/k = Bsum/(n-k), where k = A.size() and 1 <= k <= n/2;
  Asum = totalSum*k/n, which is an integer. So we have totalSum*k%n == 0;
  不要求 Asum, 和 Bsum一样, 只要totalSum*k%n == 0  --》 totalSum*(n-k)%n == 0;

  还要保证 if totalSum* k%n == 0时候, k个数组成的和可以是 totSum * k / n

已知：
    Asum/k =  Bsum/(n-k)
Then
    Asum/k =  (totalSum - Asum)/(n-k)
    totSum*k - Asum*k = Asum*n - Asum*k
    totSum * k = Asum * n
    totSum / n = Asum / k

If totalSum*k%n == 0, totalSum*(n-k)%n must == 0, because totalSumn%n == 0 and totalSum*k + totalSum*(n-k) == totalSum*n
*/

class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), total = accumulate(A.begin(), A.end(),0), m = n/2;
        
        bool hassolution = false;
        for(int i = 1; i<=m && !hassolution; i++)
            if(total*i%n == 0)
                hassolution = true;
        if(!hassolution) return false;
        vector<unordered_set<int>>dp(m+1);   //dp[i] 表示i个数组成的和, 
        dp[0] = {0};
        for(int num: A)         
            for(int i = m; i>=1; i--) //注意：不能一个数算几次，比如 A = [1,3,5],  dp[2] 不能有 2(两个1)
                for(auto t: dp[i-1])
                    dp[i].insert(t+num);
        
        for(int i = 1; i<=m; i++)
            if(total*i%n == 0 && dp[i].count(total*i/n)) return true;
        return false;

    }
};


class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), tot = 0;
        for(auto i: A) tot += i;
        
        bool hasSolution = false;
        for(int i = 1; i<n && !hasSolution; ++i)
            if(tot * i % n == 0)
                hasSolution = true;
        if(!hasSolution) return false;
        
        unordered_map<int,unordered_map<int,unordered_map<int,bool>>>dp; //需要Memoization, 否则TLE
        for(int i = 1; i<=n/2; ++i)
            if(tot * i % n == 0 && has(dp, A, 0, i, tot * i / n))
                return true;
        return false;
    }
    
    bool has(unordered_map<int,unordered_map<int,unordered_map<int,bool>>>&dp, vector<int>& A, int i, int k, int target){
        if(dp.count(i) && dp[i].count(k) && dp[i][k].count(target))
            return dp[i][k][target];
        if(k== 0 || target <= 0 || i >= A.size())
            return target == 0 && k == 0;
        for(int j = i; j<A.size(); ++j)
            if(has(dp, A, j+1, k-1, target - A[j])){
                return dp[i][k][target] = true;
            }
        return dp[i][k][target] = false;
    }
};

/**
 Method 2: 

 Bit 

比如 A = [1,2,3,4,5,6], 

A  P (其他位是0)
1 [1, 2,  0,  0,    0, 0]      (2 = 11), 由一个数组成的可以是 1
2 [1, 6,  8,  0,    0, 0]     6 = 110, 一个数组成可以是1,2,    8 = 1000, 两个数组成可以是3
3 [1, 14, 56, 64,   0, 0]   14 = 1110, 一个数组成可以是1,2,3,  56 = 111000, 两个数组成可以是3,4,5    64 = 1000,000, 三个数组成可以是6
4 [1, 30, 248,960, 1024, 0]  30 = 111,10  一个数组成可以是1,2,3,4,  248 = 11,111,000, 两个数组成可以是3,4,5,6,7,  960 =1,111,000,000 三个数组成可以是  6,7,8,9
5 [1, 62, 1016, 8128, 30720, 1024]



 */
bool splitArraySameAverage(vector<int>& A) {        
    int N = A.size(), S = 0;
    for (int a : A) S += a;
    bitset<300001> p[N] = {1};  //p[i][10] = 1 表示 由i个数组成的和 可以是10,    初始为1，是第0位为1，  只有p[0] = 1, 
    for (int a : A)
        for (int n = N - 2; n >= 0; n--)
            p[n+1] |= p[n] << a; //
    for (int n = 1; n < N; n++)
        if (S*n%N == 0  &&  p[n][S*n/N])
            return true;
    return false;
}



class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        if(A.size()<=1) {
            return false;
        }
        int n = A.size();
        int Sum = 0;
        for(auto x: A) Sum += x;
        
        int dp[Sum+1];
        memset(dp, 0, sizeof dp); //比如 dp[i] = x111000, 表示3个，4个 或者5个数的和可以是i
        dp[A[0]] = 2;
        for(int i=1; i<n; i++) {
            for(int s=Sum-A[i]; s>=0; s--) {//一定是倒叙，否则A[i] 会被重复算
                if(dp[s])
                    dp[s+A[i]] |= (dp[s]<<1);
            }
            dp[A[i]] |= 2; //因为后面是(1<<len)
            //2 = 10, 表示A[1] 一个数可以组成sum 为 A[i]
        }
        for(int len=1; len<n; len++) {
            if( (Sum*len)%n == 0 && ((1<<len) & dp[Sum*len/n])) {
                return true;
            }
        }
        return false;
    }
};

/**
 Method 3:

dp[n][k][s] = dp[n-1][k][s] || dp[n-1][k-1][s - A[n - 1]]


where dp[n][k][s] means whether sum s could be achieved by summing up k numbers 

selected among the first n numbers in given array.

Notice that the dp[n & 1] stuff in my code is just for saving space (otherwise you got error),
 which means dp[n] in above expression.
 */


class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        static bool dp[2][16][300001];
        int sum = 0;
        for (int a: A) sum += a;
        
        int N = A.size();
        memset(dp, 0, sizeof(dp));
        for (int n = 0; n <= N; n++) {
            dp[n & 1][0][0] = true;
        }
        for (int n = 1; n <= N; n++) {
            for (int k = 1; k <= N/2; k++) {
                for (int s = 1; s <= sum; s++) {
                    if (s >= A[n - 1]) {
                        dp[n & 1][k][s] = dp[n-1 & 1][k][s] || dp[n-1 & 1][k-1][s - A[n - 1]];
                    } else {
                        dp[n & 1][k][s] = dp[n-1 & 1][k][s];
                    }
                }
            }
        }
        for (int k = 1; k <= N/2; k++) {
            if ((k * sum / N * N == k * sum) && dp[N & 1][k][k * sum / N]) return true;
        }
        return false;
    }
};