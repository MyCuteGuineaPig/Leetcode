

/*
It is actually confusing that the example shown in the problem description is not the best stragety to guess the final target number, 
and the problem itself is asking for the lowest cost achieved by best guessing strategy.
The example description should be updated.

---POSSIBLY, it can also add some example about the BEST Strategy---
The example description should be:

first introduce best strategy to guess:

for one number, like 1, best strategy is 0$
for two number, like 3,4, best strategy is 3$, which can be understood in this way: you have two way to guess: 
    a) start by guess 4 is the target, 
        (the worst case is) if wrong, you get charged $4,
         then immediately you know 3 is the target number, get get charged $0 by guessing that, 
        and finally you get charged $4. 
        
    b) similarly, if you start by 3, (the worst case is) if wrong, you get charged $3, 
        then you immediately know that 4 is the target number, and get charged $0 for guessing this, 
        and finally you get charged $3. In summary:
        range ---------> best strategy cost
        3, 4 ---------> $3
        5, 6 ---------> $5
…
for three number, the best strategy is guess the middle number first, 
and (worst case is) if wrong, you get charged that middle number money, 
and then you immediately know what target number is by using “lower” or “higher” response, so in summary:
range ---------> best strategy cost
3, 4, 5 ---------> $4
7, 8, 9 ---------> $8


for four numbers, the best strategy is the first number + the third number
for five numbers, the best strategy is the second number + the fourth number

…
for more numbers, it can simply be reduced them into smaller ranges, 
and here is why DP solution make more sense in solving this.

suppose the range is [start, end]
the strategy here is to iterate through all number possible and select it as the starting point, say for any k between start and end, 
the worst cost for this is: k+DP( start, k-1 ) + DP(k+1, end ), and the goal is minimize the cost, 
so you need the minimum one among all those k between start and end




why it's using max(dp[i][x-1], dp[x+1][j])?

dp[i][j] is the minimal cost to guess from range(i...j). 
比如 [1,2,3,4,5,6], 先选3, 如果比3大，cost = 3 + 5,  如果比 3小, cost = 3 + 1 = 4,  8 is guarantee cost 

*/


/*

如果binary search的话，先猜中间的，因为会告诉是大还是小，所以猜了中间的，只要cost是多的哪个半个就行, k+dp(k+1,end), k是binary search猜的数
*/

/*

下面code 顺序是
 [1,2]
 [2,3]  [1,3]
 [3,4]  [2,4], [1,0]


 */

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1,vector<int>(n+1,0));
        for(int j = 2; j<=n; j++){
            for(int i = j-1; i>=1; i--){
                int localmax = 0, globalmin = numeric_limits<int>::max();
                for(int k = i+1; k<j; k++){
                    localmax = k + max(dp[i][k-1],dp[k+1][j]);
                    globalmin = min(globalmin,localmax);
                }
                dp[i][j] = (j == i+1 ? i: globalmin);
            }
        }
        return dp[1][n];
    }
};


/*
dp[i][j] 表示从 i 到 j 最小cost
当 dp[i][i] cost = 0
dp[i][i+1] cost = i  比如 2-3, 先猜2, 如果错了，知道是3, cost = 2   

dp[i][j] = max(dp[i][k-1], dp[k+1][j]) + k,  k 是猜的数

 */

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1, vector<int>(n+1, numeric_limits<int>::max()));
        //dp[1] = 0; dp[0] = 0;
        for(int i = 1; i <=n; ++i )
            dp[i][i] = 0;
        for(int i = 1; i <n; ++i)
            dp[i][i+1] = i;

        for(int len = 2; len < n; ++len){
            for(int i = 1; i + len <= n; ++i){
                for (int k = i + 1; k < i + len; ++k)
                    dp[i][i+len] = min(dp[i][i+len], max(dp[i][k-1], dp[k+1][i+len])+k);
            }
        }
    
        return dp[1][n];
    }
};

//or 
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1, vector<int>(n+1, numeric_limits<int>::max()));
        //dp[1] = 0; dp[0] = 0;
        for(int i = 1; i <=n; ++i )
            dp[i][i] = 0;
        for(int i = 1; i <n; ++i)
            dp[i][i+1] = i;

        for(int j = 3; j <= n; ++j){
            for(int i = j - 2; i >= 1; --i){
                for (int k = i + 1; k < j; ++k){
                    dp[i][j] = min(dp[i][j], max(dp[i][k-1], dp[k+1][j])+k);
                }
            }
        }
    
        return dp[1][n];
    }
};


// top-down
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1, vector<int>(n+1, numeric_limits<int>::max()));
        auto f = [&](this auto && f, int i, int j){
            if (i == j ) {
                return 0; 
            }
            if (i == j -1) {
                return i;
            }
            if (dp[i][j] != numeric_limits<int>::max())
                return dp[i][j];
            for(int k = i + 1 ; k < j; ++k){
                dp[i][j] = min(dp[i][j], max(f(i, k-1), f(k+1, j)) + k);
                
            }
                
            return dp[i][j];
        };
        return f(1, n);
    }
};


// 2020 Botton-up
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1, vector<int>(n+1));
        for(int i = 1; i<n; ++i){ // 长度
            for(int j = 1; j+i<=n; ++j){ // 起点
                int cur = numeric_limits<int>::max();
                for(int k = j; k<=j+i; ++k){ //pick的点
                    int left = 0, right = 0;
                    if(k>j) left = dp[j][k-1];
                    if(k<j+i) right = dp[k+1][j+i];
                    cur = min(max(left,right)+k, cur);
                }
                dp[j][j+i] = cur;
            }
        }
        return dp[1][n];
    }
};


//2020 Top-Down
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1,vector<int>(n+1,-1));
        return topDown(dp, 1, n);
    }
    
    int topDown(vector<vector<int>>&dp, int l, int r){
        if(l >= r)
            return 0;
        if(dp[l][r] >= 0)
            return dp[l][r];
        int cur = numeric_limits<int>::max();
        for(int k = l; k <= r; ++k){
            cur = min(cur, k + max(topDown(dp, l, k-1), topDown(dp, k+1, r)));
        }
        return dp[l][r] = cur;
    }
};


/**
 Optimization: 

 When selecting the first guess, the loop starts from one index left to the middle ((start + end) / 2 ), 
 and the loop break when the cost of left part is higher than the cost of right part.

 */
class Solution {    
public:
    int calc(int l, int r, vector<vector<int>>& dp) {
        if(dp[l-1][r-1]>=0) return dp[l-1][r-1];
        switch(r-l+1) {
            case 0: return 0;
            case 1: return 0;
            case 2: return l;
            case 3: return l+1;
            case 4: return l+l+2;
            case 5: return l+l+4;
        }
        int res=INT_MAX, mi, sl=INT_MIN, sr=INT_MAX; // sl (sum left) and sr (sum right) are used for optimisation
        for(mi=(l+r)/2;mi<r && sl<sr;mi++) {
            int sl = calc(l, mi-1, dp), sr = calc(mi+1,r, dp);
            res=min(res, mi + max(sl, sr));
        }
        dp[l-1][r-1]=res;
        return res;
    }
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n,vector<int>(n,-1));
        return calc(1,n,dp);
    }
};

//https://blog.csdn.net/Site1997/article/details/100168676
/**
 顺序是 
 [1,2]
 [2,3], [1,3]
 [3,4], [2,4], [1,4] ==> deque 存的是 (3,4), 然后(2,4)的值，再对比当前k值

deque is descending stack, k 在减小, f(k+1,b)+k 在增大

 */
class Solution {    
public:
    int getMoneyAmount(int n) {
        dp = vector<vector<int>>(n+5, vector<int>(n+5, 0));
        for (int r=2; r<=n; r++) {
            int k = r-1;
            //        <k  , dp[l+1][r] + l>
            deque< pair<int, int> > dq;
            for (int l=r-1; l>0; l--) {
                while (k > 0 && dp[l][k-1] > dp[k+1][r])
                    k --;
                // get rid of idx that is lager than k
                while (!dq.empty() && dq.back().first > k) // deque 的k 大于 k, 要找f(k+1,b)+k的k 必须小于等于k, 看blog的图
                    dq.pop_back();
                // insert current dp[l+1][r] + l into deque
                int dpVal = dp[l+1][r] + l;   //因为dpVal 跟上一个比是 f[k1][b] >= f[k2][b] given k1 <= k2, 所以pop_front 确保deque 是递减的
                while (!dq.empty() && dq.front().second > dpVal)
                    dq.pop_front();
                dq.push_front(make_pair(l, dpVal));
                dp[l][r] = min(dp[l][k] + k + 1, dq.back().second);
            }
        }
        return dp[1][n];
    }
};
