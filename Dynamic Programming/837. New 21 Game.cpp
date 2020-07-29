/*
Case: N=3, K=1, W=10
    i=1 (drawn card-1) : You win as you get 1(1<=N), P(i=1)=1/10=0.1
    i=2 (drawn card-2) : You win as you get 2(2<=N), P(i=2)=1/10=0.1
    i=3 (drawn card-3) : You win as you get 3(3<=N), P(i=3)=1/10=0.1
All events are independent: Total prob = 0.1+0.1+0.1 = 0.3

Case: N=3, K=2, W=10
    i=1 (draw 1) P(draw=1)=0.1 [call this A], Same event, we do not stop now we can draw either 1 or 2 , as i<K, for drawing 1 or 2 , P(1 or 2)=0.1+0.1=0.2 [call this B], P(complete draw) = P(A)xP(B)=0.1x0.2 = 0.02
    i=2 (drawn card-2) : You win as you get 2(2<=N) and you stop as 2>=K, P(i=2)=1/10=0.1
    i=3 (drawn card-3) : You win as you get 3(3<=N) and you stop as 2>=K, P(i=3)=1/10=0.1

这个计算方法跟Lee的是反过来的，但是最后的结果（本质）是一样的。
而Lee的思路是，p[i]（dp[i]） 是得到这个点的概率，比如w(范围)是[1,10]. K =3
    i=1(抽中1分的概率)就是 1/10.
    i=2: 0.1(抽中2分的概率)+0.1x0.1(两次抽中1)的概率
    i=3: 0.1 (抽中3分的概率) + 0.1x0.1(第一次抽中1，第二次抽中2) + 0.1x0.1(第一次抽中2，第二次抽中1)+0.1x0.1x0.1（三次抽中0.1）
可以从公式里面归纳出
    i=1:
        0.1x1
    i=2:
        0.1x(1+0.1) = 0.11
    i=3:
        0.1(1+0.1+0.1+0.01) = 0.1(1+0.1+0.11) 括号里是之前的p的sum，以此来推出Wsum的公式
那为什么>k之后，几不变了呢，例如k=3
    i=4: 0.1(抽中4)+0.1x0.1(抽中1 and 3) +0.1x0.1(抽中2 and 2)+0.1x0.1x0.1(抽中2个1，一个2)
    i=5: 0.1(抽中4)+0.1x0.1(抽中1 and 4) +0.1x0.1(抽中2 and3)+0.1x0.1x0.1(抽中2个1，一个3)
…
可以看到，最后大于k的公式后面都是一样的。因为3（k）是一道坎，只有抽中小于3的数，后面才可能继续抽。

最后。。如果i-w >0, 比如say W = 10, when we reach i = 11, dp[i] = Wsum / W = (dp[1] + .. + dp[10]) /10
    i = 11是不可能一次抽中的（大于w），所以要把一次抽中的概率减去，就是第一次。
    i = 12不可能跟2一样（抽中1一次11，再抽中1，也不可能一下抽中12）要把这次概率减去。

 */



class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0 || N >= K + W) return 1.0;// 因为当在 K 时候就停下来了, 最大数是 K-1 + N
        vector<double> dp(N + 1);
        dp[0] = 1.0;
        double Wsum = 1.0, res = 0.0;
        for (int i = 1; i <= N; ++i) {
            dp[i] = Wsum / W;
            if (i < K) Wsum += dp[i]; else res += dp[i];
            if (i - W >= 0) Wsum -= dp[i - W];
        }
        return res;
    }
};


/*
The transition equation from the first solution is:
dp[i] = 1/w * (dp[i - 1] + dp[i - 2] + ... + dp[i - W])

Substitute all the i with i -1
dp[i-1] = 1/w * (dp[(i - 1) - 1] + dp[(i - 1) - 2] + ... + dp[(i - 1) - W]) = 1/w * (dp[i - 2] + dp[i - 3] + ... + dp[i - 1 - W])

Let's format the equations like this:
(1)  dp[i]      = 1/w * (dp[i - 1] + dp[i - 2] + dp[i - 3] + ... + dp[i - W])
(2)  dp[i-1]    = 1/w * (            dp[i - 2] + dp[i - 3] + ... + dp[i - W] + dp[i - 1 - W])

From (1), subtract (2). Everything from dp[i - 2] to dp[i - W] are cancelled out, leaving only:
dp[i] - dp[i-1] = 1/w * (dp[i - 1] - dp[i - 1 - W]);

Move dp[i-1] to the right. Now we have an equation where each i is only depending on i - 1
dp[i] = dp[i-1] + 1/w * (dp[i - 1] - dp[i - 1 - W]);


 */


class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) {
            return 1;
        }
        vector<double>dp(N + 1);
        dp[0] = 1;
        for (int i = 1; i <= N; i++) {
            dp[i] = dp[i - 1];
            if (i <= W) {
                dp[i] += dp[i - 1] / W;
            } else {
                dp[i] += (dp[i - 1] - dp[i - W - 1]) / W;
            }
            if (i > K) {
                dp[i] -= (dp[i - 1] - dp[K - 1]) / W; //因为pick 到 k 就停了，不会继续pick， 所以减去大于等于K之后再pick的概率
            }
        }
        return dp[N] - dp[K - 1];
    }
};

class Solution {
public:
    double new21Game(int N, int K, int W) {
        if(N >= K+W-1) return 1.0; // all possibilities of positions after alice stops playing are from [K, K+W-1]

        vector<double> p(N+1);
        double prob = 1/(W+0.0); // single elem probability

        double prev = 0;

        p[0] = 1; // Since we start from 0, initialize it to 1

         //Until K
        for(int i = 1; i <= K; i++) {
            prev = prev - (i-W-1 >= 0 ? p[i - W -1] : 0) + p[i-1];
            p[i] = prev*prob;
        }

        double req = p[K];

        // From K+1, we don't add the p[i-1] term here as it is >= K
        for(int i = K+1; i <= N; i++) {
            prev = prev - (i-W-1 >= 0 ? p[i - W -1] : 0);
            p[i] = prev * prob;
            req += p[i];
            //System.out.println(p[i]);
        }

        return req;
    }
};


class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) {
            return 1;
        }
        vector<double> p(K + W, 0);
        p[0] = 1;
        double sum = 1;
        for (int i = 1; i < K + W; i++) {
            p[i] += 1.0 / W * sum;
            if (i < K) {
                sum += p[i];
            }
            if (i - W >= 0) {
                sum -= p[i - W];
            }
        }
        return accumulate(p.begin() + K, p.begin() + min(N + 1, K + W), 0.0);
    }
};

/**
 Method 3:

F(x) = (F(x+1) + F(x+2) + ... + F(x+W)) / W
F(x+1) = (F(x+2) + F(x+3) + ... + F(x+1+W)) / W

After a substraction, we have

F(x) = F(x+1) - 1/W * (F(x+1+W) - F(x+1))


 */

class Solution {
public:
    double new21Game(int N, int K, int W) {
        unordered_map<int,double>dp;
        return topDown(N, K, W, 0, dp);
    }
    
    double topDown(int N, int K, int W, int cur, unordered_map<int,double>&dp){
        if(cur == K-1)
            return (double)min(N-K+1, W)/W;
        if (cur > N)
            return 0;
        else if(cur >= K)
            return 1.0;
        
        if(dp.count(cur))
            return dp[cur];
        double prob = topDown(N, K, W, cur + 1, dp) - (topDown(N,K,W,cur+1+W,dp)-topDown(N,K,W,cur+1,dp))/W;
        return dp[cur] = prob;
    }
};


/*
Method 4

 dp[i] =  21Game(N-K+i+1, i+1, W), so that dp[K-1] == new21Game(N,K,W)

            1. 1/W *[ Sum( 1 <= i <= k-1 21Game(N-i, K-i, W)) + min (N, W) - K +1  ] if W>=K
21Game = {  
            2. 1/W * Sum( 21Game(N-i, K-i, W) )  if W<K


1/W *[ Sum( 21Game(N-i, K-i, W)) + min (N, W) - K +1  W >= K

If W >= K, then W-K+1 of these states are terminal
    比如 W = 10, , K = 3,  W-K+1 = 8 个(3,4,5,6,7,8,9,10)都没有再move, 


 */


class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1.0;
        vector<double> dp(K);
        auto total = 0.0;
        for (auto i = 0; i < K; ++i) {
            if (i < W) dp[i] = (total + min(N-K+1,W-i)) / W;
            else dp[i] = total / W, total -= dp[i-W];
            total += dp[i];
        }
        return dp[K-1];
    }
};